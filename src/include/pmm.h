/*
 * =====================================================================================
 *
 *       Filename:  pmm.h
 *
 *    Description:  页面内存管理
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

#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

// 线程栈的大小
#define STACK_SIZE 8192

// 物理内存管理的栈地址，我们定在了寻址空间的较高位置
// 我们要能通过这个地址管理所有的内存
#define PMM_STACK_ADDR 	0xFF000000

// 支持的最大物理内存(512MB)
#define PMM_MAX_SIZE 0x20000000

// 物理内存页框大小 
#define PHY_PAGE_SIZE 0x1000

// 页掩码 按照 4096 对齐地址
#define PHY_PAGE_MASK 0xFFFFF000

// 内核文件在内存中的起始和结束位置
// 在链接器脚本中要求链接器定义
extern uint8_t kern_start[];
extern uint8_t kern_end[];

// 输出 BIOS 提供的物理内存布局
void show_memory_map();

// 初始化物理内存管理
void init_pmm();

// 返回一个内存页的物理地址
uint32_t pmm_alloc_page();

// 释放申请的内存
void pmm_free_page(uint32_t p);

#endif 	// INCLUDE_PMM_H

