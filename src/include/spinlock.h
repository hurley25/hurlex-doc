/*
 * =====================================================================================
 *
 *       Filename:  spinlock.h
 *
 *    Description:  内核自旋锁
 *
 *        Version:  1.0
 *        Created:  2013年11月23日 20时51分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_SPINLOCK_H_
#define INCLUDE_SPINLOCK_H_

#include "types.h"

typedef
struct spinlock_t {
	volatile uint32_t lock;
} spinlock_t;

// 1 表示 spinlock 可用
// 程序应调用初始化函数而不是使用这个宏初始化
#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 }

// 初始化自旋锁
#define spin_lock_init(x) do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)

// spinlock 加锁
static inline void spinlock_lock(spinlock_t *lock)
{
	asm volatile ( "\n1:\t"
			"lock; decb %0\n\t" 			// decb 将 lock->lock 减 1，lock 表示要锁住地址总线
			"js 2f\n\t" 
			".section .text.lock, \"ax\"\n"
			"2:\t" 
			"cmpb $0, %0\n\t" 
			"rep; nop\n\t" 
			"jle 2b\n\t" 
			"jmp 1b\n\t" 
			".previous"
			:"=m" (lock->lock) : : "memory" ); 
}

// spinlock 解锁
static inline void spinlock_unlock(spinlock_t *lock)
{
	asm volatile ( "movb $1, %0" 
			:"=m" (lock->lock) : : "memory" );
}


#endif 	// INCLUDE_SPINLOCK_H_
