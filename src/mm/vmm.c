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
pgd_t pgd_kern[PGD_SIZE];

// 内核固定映射页表
pte_t pte_kern[PTE_COUNT][PTE_SIZE];

void init_vmm()
{
	// 0xC0000000 这个地址在页目录的索引
	uint32_t kern_pte_first_idx = PGD_INDEX(PAGE_OFFSET);
	
	int i;
	for (i = kern_pte_first_idx; i < PTE_COUNT + kern_pte_first_idx; i++) {
		// 此处是内核虚拟地址，MMU 需要物理地址，所以减去偏移，下同
		pgd_kern[i] = (uint32_t)pte_kern[i] - PAGE_OFFSET;
	}

	// 多维数组是顺序存储的，所以强制类型转换后直接顺序初始化
	pte_t *pte = (pte_t *)pte_kern;
	for (i = 0; i < PTE_COUNT * PTE_SIZE; i++) {
		pte[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}

	uint32_t pgd_kern_phy_addr = (uint32_t)pgd_kern - PAGE_OFFSET;
	switch_pgd(pgd_kern);
}

void switch_pgd(pgd_t *pd)
{
	asm volatile ("mov %0, %%cr3" : : "r" (pd));
}

void map(pgd_t *pgd_now, uint32_t va, uint32_t pa, uint32_t flags)
{
//	uint8_t pgd_idx = PGD_INDEX(va);
//	uint8_t pte_idx = PTE_INDEX(va); 
//	
//	pte_t *pte = (pte_t *)pgd_now[pgd_idx];
//	if (!pte) {
//		pte = pmm_alloc_page();	
//		bzero(pte, 0x1000);
//		pgd_now[pgd_idx] = pte | PAGE_PRESENT | PAGE_WRITE;
//	}
//
//	pte[pte_idx] = (pa & PAGE_MASK) | flags;
//
//	// 通知 CPU 更新页表缓存
//	asm volatile ("invlpg (%0)" : : "a" (va));
}

void unmap(pgd_t *pgd_now, uint32_t va)
{
	/*uint8_t pgd_idx = PGD_INDEX(va);
	uint8_t pte_idx = PTE_INDEX(va);

	pte_t *pte = pgd_now[pgd_idx];

	pte[pte_idx] = 0;

	// 通知 CPU 更新页表缓存
	asm volatile ("invlpg (%0)" : : "a" (va));*/
}

uint32_t get_mapping(pgd_t *pgd_now, uint32_t va, uint32_t *pa)
{
	/*uint8_t pgd_idx = PGD_INDEX(va);
	uint8_t pte_idx = PTE_INDEX(va);

	pte_t *pte = pgd_now[pgd_idx];
	if (!pte) {
	      return 0;
	}
	
	// 如果地址有效而且指针不为NULL，则返回地址
	if (pte[pte_idx] != 0 && pa) {
		 *pa = pte[pte_idx] & PAGE_MASK;
		return 1;
	}

	return 0;*/
}

