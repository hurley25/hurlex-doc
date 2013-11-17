/*
 * =====================================================================================
 *
 *       Filename:  pmm.c
 *
 *    Description:  页内存管理
 *
 *        Version:  1.0
 *        Created:  2013年11月16日 12时00分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "multiboot.h"
#include "common.h"
#include "debug.h"
#include "pmm.h"
#include "vmm.h"

// 当前申请到的位置
uint32_t pmm_stack_loc = PMM_STACK_ADDR;

// 内存申请的界限位置
uint32_t pmm_stack_max = PMM_STACK_ADDR;

void show_memory_map()
{
	uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
	uint32_t mmap_length = glb_mboot_ptr->mmap_length;

	printk("Memory map:\n");

	mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
	for (mmap = (mmap_entry_t *)mmap_addr; (uint32_t)mmap < mmap_addr + mmap_length; mmap++) {
		printk("base_addr = 0x%X%08X, length = 0x%X%08X, type = 0x%X\n",
			(uint32_t)mmap->base_addr_high, (uint32_t)mmap->base_addr_low,
			(uint32_t)mmap->length_high, (uint32_t)mmap->length_low,
			(uint32_t)mmap->type);
	}
}

void init_pmm()
{
}

void init_page_pmm()
{	
	mmap_entry_t *mmap_start_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr;
	mmap_entry_t *mmap_end_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr + glb_mboot_ptr->mmap_length;

	mmap_entry_t *map_entry;

	for (map_entry = mmap_start_addr; map_entry < mmap_end_addr; map_entry++) {

		// 如果是可用内存 ( 按照协议，1 表示可用内存，其它数字指保留区域 )
		if (map_entry->type == 1 && map_entry->base_addr_low == 0x100000) {
			
			// 把这些内存段，按页存储到页管理栈里
			uint32_t j = map_entry->base_addr_low;

			// 物理页面必须按照 4096 字节对齐
			j += (((uint32_t)kern_end - (uint32_t)kern_start + PHY_PAGE_SIZE) & PHY_PAGE_MASK);

			while (j < map_entry->base_addr_low + map_entry->length_low && j <= PMM_MAX_SIZE) {
				pmm_free_page(j);
				j += 0x1000;
			}
		}
	}
}

uint32_t pmm_alloc_page()
{
	// 确认栈地址没有下溢
	// 在分页开启以后，需要先收集空闲内存放入管理栈才可以进一步申请内存
	// 否则之掉调用申请内存页会出错
	if (pmm_stack_loc == PMM_STACK_ADDR) {
		panic("Error: Out of Memory!");
	}
	// 相当于出栈
	pmm_stack_loc -= sizeof(uint32_t);
	uint32_t *stack = (uint32_t *)pmm_stack_loc;

	return *stack;
}

void pmm_free_page(uint32_t p)
{
	// 此处意为存储空闲页面的内存页写满了
	// 需要映射一页内存来存储索引
	if (pmm_stack_loc == pmm_stack_max) {
		map(pmm_stack_max, p, PAGE_PRESENT | PAGE_WRITE);
		pmm_stack_max += 4096;
	} else {
		// 将这个空闲的内存页地址存入管理栈
		uint32_t *stack = (uint32_t*)pmm_stack_loc;
		*stack = p;
		pmm_stack_loc += sizeof(uint32_t);
	}
}

