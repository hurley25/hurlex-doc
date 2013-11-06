/*
 * =====================================================================================
 *
 *       Filename:  panic.c
 *
 *    Description:  打印栈信息
 *
 *        Version:  1.0
 *        Created:  2013年11月06日 22时57分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "panic.h"
#include "printk.h"
#include "common.h"
#include "elf.h"

static void print_stack_trace();

extern elf_t kernel_elf;

void panic(const char *msg)
{
	printk("*** System panic: %s\n", msg);
	print_stack_trace();
	printk("***\n");
	
	// 致命错误发生后打印栈信息后停止在这里
	while(1);
}

void print_stack_trace()
{
	uint32_t *ebp, *eip;

	asm volatile ("mov %%ebp, %0" : "=r" (ebp));
	while (ebp) {
		eip = ebp + 1;
		printk("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
		ebp = (uint32_t *)*ebp;
	}
}

