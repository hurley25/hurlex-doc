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

#include "common.h"
#include "debug.h"
#include "pmm.h"

// 没有开启分页机制时的内存管理方案采用的管理指针
uint32_t pmm_location;

void init_pmm()
{
	// 简单起见，内存 0～640 KB 是空闲的
	// 我们直接把原始的物理内存页管理起始地址设为 0
	pmm_location = 0;
}

uint32_t pmm_alloc_page()
{
	// 0x1000 即 4096D，每页内存 4 KB
	pmm_location += 0x1000;

	return pmm_location;
}

