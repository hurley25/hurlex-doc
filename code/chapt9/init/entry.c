/*
 * =====================================================================================
 *
 *       Filename:  entry.c
 *
 *    Description:  hurlex 内核的入口函数
 *
 *        Version:  1.0
 *        Created:  2013年10月31日 13时31分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"

int kern_entry()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	printk_color(rc_black, rc_green, "Hello, OS kernel!\n");

	init_timer(200);
	
	// 开启中断
	// asm volatile ("sti");

	printk("kernel in memory start: 0x%08X\n", kern_start);
	printk("kernel in memory end:   0x%08X\n", kern_end);
	printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);
	
	show_memory_map();
	init_pmm();

	printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	uint32_t allc_addr = NULL;
	printk_color(rc_black, rc_light_brown, "Test Physical Memory Alloc :\n");
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);

	return 0;
}

