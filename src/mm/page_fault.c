/*
 * =====================================================================================
 *
 *       Filename:  page_fault.c
 *
 *    Description:  页错误处理函数
 *
 *        Version:  1.0
 *        Created:  2013年11月17日 16时54分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "vmm.h"
#include "debug.h"

void page_fault(pt_regs *regs)
{
	uint32_t cr2;
	asm volatile ("mov %%cr2, %0" : "=r" (cr2));

	printk("Page fault at EIP: 0x%x, virtual faulting address 0x%x\n", regs->eip, cr2);
	printk("Error code: %x\n", regs->err_code);

	// bit 0 为 0 指页面不存在内存里
	if ( !(regs->err_code & 0x1)) {
		printk_color(rc_black, rc_red, "Because the page wasn't present.\n");
	}
	// bit 1 为 0 表示读错误，为 1 为写错误
	if (regs->err_code & 0x2) {
		printk_color(rc_black, rc_red, "Write error.\n");
	} else {
		printk_color(rc_black, rc_red, "Read error.\n");
	}
	// bit 2 为 1 表示在用户模式打断的，为 0 是在内核模式打断的
	if (regs->err_code & 0x4) {
		printk_color(rc_black, rc_red, "In user mode.\n");
	} else {
		printk_color(rc_black, rc_red, "In kernel mode.\n");
	}
	// bit 3 为 1 表示错误是由保留位覆盖造成的
	if (regs->err_code & 0x8) {
		printk_color(rc_black, rc_red, "Reserved bits being overwritten.\n");
	}
	// bit 4 为 1 表示错误发生在取指令的时候
	if (regs->err_code & 0x10) {
		printk_color(rc_black, rc_red, "The fault occurred during an instruction fetch.\n");
	}

	while (1);
}

