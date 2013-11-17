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
	// 简单起见，内存 0～640 KB 是空闲的
	// 我们直接把原始的物理内存页管理起始地址设为 0
	pmm_location = 0;
}

uint32_t pmm_alloc_page()
{
	// 根据是否开启分页决定对内存的管理策略
	if (mm_paging_active) {
		// TODO
	}

	// 0x1000 即 4096D，每页内存 4 KB
	pmm_location += 0x1000;

	return pmm_location;
}

void pmm_free_page(uint32_t p)
{
	// TODO
}

