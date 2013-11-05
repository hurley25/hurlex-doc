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

#include "multiboot.h"
#include "console.h"

int kern_entry(multiboot_t *mboot_ptr)
{
	monitor_clear();

	monitor_write_color("Hello, OS kernel!\n", rc_black, rc_green);

	return 0;
}

