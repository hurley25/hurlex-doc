/*
 * =====================================================================================
 *
 *       Filename:  task.h
 *
 *    Description:  进程管理相关的定义
 *
 *        Version:  1.0
 *        Created:  2013年11月20日 09时18分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_PROCESS_H_
#define INCLUDE_PROCESS_H_

#include "types.h"
#include "list.h"
#include "pmm.h"

// 最大进程数
#define MAX_PROCESS 	1024

// 进程状态描述
typedef
enum task_state {
	TASK_UNINIT = 0, 	// 未初始化
	TASK_SLEEPING = 1, 	// 睡眠中
	TASK_RUNNABLE = 2, 	// 可运行(也许正在运行)
	TASK_ZOMBIE = 3, 	// 僵尸状态
} task_state;

// 内核线程的上下文切换保存的信息
struct context {
    uint32_t cr3;
    uint32_t eip;
    uint32_t esp, ebp;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
};

// 当前的 pid 值
extern pid_t now_pid;

// 进程控制块 PCB 
struct task_struct {
	volatile task_state state; 	// 进程当前状态
	pid_t 	 pid; 			// 进程标识符
	void  	*stack; 		// 进程的内核栈地址
	struct mm_struct *mm; 		// 当前进程的内存地址映像
	struct context context; 	// 进程切换需要的上下文信息
	struct list_head list; 		// 进程的链表
};

// 初始化任务调度
void init_task();

#endif 	// INCLUDE_PROCESS_H_

