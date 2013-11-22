/*
 * =====================================================================================
 *
 *       Filename:  tss.h
 *
 *    Description:  TSS 段相关函数
 *
 *        Version:  1.0
 *        Created:  2013年11月20日 09时52分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_TSS_H_
#define INCLUDE_TSS_H_

#include "types.h"

// 任务段描述符结构
typedef
struct tss_entry_struct {
    uint32_t ts_link;
    uint32_t ts_esp0;
    uint16_t ts_ss0;
    uint16_t ts_padding1;
    uint32_t ts_esp1;
    uint16_t ts_ss1;
    uint16_t ts_padding2;
    uint32_t ts_esp2;
    uint16_t ts_ss2;
    uint16_t ts_padding3;
    uint32_t ts_cr3;
    uint32_t ts_eip;
    uint32_t ts_eflags;
    uint32_t ts_eax;
    uint32_t ts_ecx;
    uint32_t ts_edx;
    uint32_t ts_ebx;
    uint32_t ts_esp;
    uint32_t ts_ebp;
    uint32_t ts_esi;
    uint32_t ts_edi;
    uint16_t ts_es;
    uint16_t ts_padding4;
    uint16_t ts_cs;
    uint16_t ts_padding5;
    uint16_t ts_ss;
    uint16_t ts_padding6;
    uint16_t ts_ds;
    uint16_t ts_padding7;
    uint16_t ts_fs;
    uint16_t ts_padding8;
    uint16_t ts_gs;
    uint16_t ts_padding9;
    uint16_t ts_ldt;
    uint16_t ts_padding10;
    uint32_t ts_iomap;
} __attribute__((packed)) tss_entry_t;

// 修改内核栈地址
void load_kern_esp(uint32_t esp0);

// TSS 刷新[汇编实现]
extern void tss_flush();

#endif 	// INCLUDE_TSS_H_
