/*
 * =====================================================================================
 *
 *       Filename:  task.c
 *
 *    Description:  内核线程的实现
 *
 *        Version:  1.0
 *        Created:  2013年11月20日 16时02分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "task.h"

// 全局 pid 值
pid_t now_pid = 0;

// 可调度进程链表
struct task_struct *running_proc_head = NULL;

// 等待进程链表
struct task_struct *wait_proc_head = NULL;

// 初始化任务调度
void init_task();

