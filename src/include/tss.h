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
    uint32_t prev_tss;   // 前一个 TSS 段
    uint32_t esp0;       // 切换到内核模式的时候加载的 esp
    uint32_t ss0;        // 切换到内核模式的时候加载的 ss
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;  
    uint32_t ss2;   
    uint32_t cr3;   
    uint32_t eip;   
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;         // 切换到内核模式的时候，es - gs 会修改
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed)) tss_entry_t;

// TSS 刷新[汇编实现]
extern void tss_flush();

#endif 	// INCLUDE_TSS_H_
