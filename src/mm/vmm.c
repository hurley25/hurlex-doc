/*
 * =====================================================================================
 *
 *       Filename:  vmm.c
 *
 *    Description:  虚拟内存管理
 *
 *        Version:  1.0
 *        Created:  2013年11月17日 16时59分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "idt.h"
#include "string.h"
#include "debug.h"
#include "vmm.h"
#include "pmm.h"

// 内核页目录地址
pgd_t *page_directory;

// 内核页表地址
pte_t *page_tables;

// 这两个宏用于页表和页目录的索引获取
#define PAGE_DIR_IDX(x) 		((uint32_t)x / 1024)
#define PAGE_TABLE_IDX(x) 		((uint32_t)x % 1024)

void init_vmm()
{
	// 创建一个页目录
	pgd_t *pd = (pgd_t *)pmm_alloc_page();

	// 清空整个页目录的数据为 0
	bzero(pd, 0x1000);

	pd[0] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;

	switch_pgd(pd);

	// PMM_STACK_ADDR 0xFF000000 物理内存管理的栈地址
	// 必须在分页模式开启之前给该项分配内存，否则会直接引起异常
	// 异常的原因是调用了 pmm_free_page 后触发 map 调用，map 会调用 pmm_alloc_page
	// 但是 pmm_alloc_age 此时无法找到可用内存，导致触发下溢条件 panic 结束
}

void switch_pgd(pgd_t *pd)
{
	asm volatile ("mov %0, %%cr3" : : "r" (pd));
}

void map(uint32_t va, uint32_t pa, uint32_t flags)
{
	uint32_t virtual_page = va / 0x1000;
	uint32_t pt_idx = PAGE_DIR_IDX(virtual_page);

	// 找到虚拟地址 va 对应的描述表，如果它没被使用的话
	if (page_directory[pt_idx] == 0) {
		page_directory[pt_idx] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;

		// 这里不再解释，原理同上
		bzero((void *)&page_tables[pt_idx * 1024], 0x1000);
	}

	// 创建好以后设置页表项，让这个地址所处的那一页内存指向目标物理内存页
	page_tables[virtual_page] = (pa & PAGE_MASK) | flags;

	// 通知 CPU 更新页表缓存
	asm volatile ("invlpg (%0)" : : "a" (va));
}

void unmap(uint32_t va)
{
	uint32_t virtual_page = va / 0x1000;

	page_tables[virtual_page] = 0;

	// 通知 CPU 更新页表缓存
	asm volatile ("invlpg (%0)" : : "a" (va));
}

char get_mapping(uint32_t va, uint32_t *pa)
{
	uint32_t virtual_page = va / 0x1000;
	uint32_t pt_idx = PAGE_DIR_IDX(virtual_page);

	// 如果当前地址没有被映射直接返回 0
	if (page_directory[pt_idx] == 0) {
	      return 0;
	}
	
	// 如果地址有效而且指针不为NULL，则返回地址
	if (page_tables[virtual_page] != 0 && pa) {
		 *pa = page_tables[virtual_page] & PAGE_MASK;
		return 1;
	}

	return -1;
}

