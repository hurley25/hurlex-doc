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

#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

#include "types.h"
#include "pmm.h"
#include "vmm.h"

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
    uint32_t esp;
    uint32_t ebp;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
};

// 进程内存地址结构
struct mm_struct {
	pgd_t *pgd_dir; 	// 进程页表
};

// 进程控制块 PCB 
struct task_struct {
	volatile task_state state; 	// 进程当前状态
	pid_t 	 pid; 			// 进程标识符
	void  	*stack; 		// 进程的内核栈地址
	struct mm_struct *mm; 		// 当前进程的内存地址映像
	struct context context; 	// 进程切换需要的上下文信息
	struct task_struct *next; 	// 链表指针
};

// 全局 pid 值
extern pid_t now_pid;

// 可调度进程链表
extern struct task_struct *running_proc_head;

// 等待进程链表
extern struct task_struct *wait_proc_head;

// 初始化任务调度
void init_task();

// 内核线程创建
int32_t kernel_thread(int (*fn)(void *), void *arg, uint32_t *stack);

// 任务切换
void switch_to(struct task_struct *next);

#endif 	// INCLUDE_TASK_H_

