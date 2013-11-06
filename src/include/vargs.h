/*
 * =====================================================================================
 *
 *       Filename:  vargs.h
 *
 *    Description:  可变形参表相关的宏定义
 *
 *        Version:  1.0
 *        Created:  2013年11月06日 12时12分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef INCLUDE_VARGS_H_
#define INCLUDE_VARGS_H_

typedef __builtin_va_list va_list;

#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap) 

#endif 	// INCLUDE_VARGS_H_
