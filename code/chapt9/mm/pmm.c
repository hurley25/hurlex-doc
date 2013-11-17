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

// 是否开启内存分页
uint8_t mm_paging_active = 0;

// 没有开启分页机制时的内存管理方案采用的管理指针
static uint32_t pmm_location;

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
	// TODO
}

uint32_t pmm_alloc_page()
{
	// TODO
	return 0;
}

void pmm_free_page(uint32_t p)
{
	// TODO
}

