/*
 *      kernel.ld -- 针对 kernel 格式所写的链接脚本
 *
 *           作者是 JamesM 先生，感谢他的慷慨和付出
 *
 *          Original file taken from Bran's Kernel Development 
 *          tutorials: http://www.osdever.net/bkerndev/index.php. 
 *
 *	首先，我们声明了内核程序的入口地址是符号 "start"
 *      这个脚本告诉 ld 程序 如何构造我们的内核映像文件。
 *      然后，我们声明了第一个段 .text 段（代码段）以及它的起始地址 0x100000（1MB）。
 *      接着是 已初始化数据段 .data 和 未初始化数据段 .bss 以及它们采用的4096的页对齐方式。
 *      Linux GCC 增加了额外的数据段 .rodata，这是一个只读的已初始化数据段，放置常量什么的。
 *      简单起见，我们把和 .data 段放在一起好了。
 *
 *      This script tells LD how to set up our kernel image. 
 *      Firstly it tells LD that the start location of our binary should be the symbol 'start'. 
 *      It then tells LD that the .text section (that's where all your code goes) should be first,
 *      and should start at 0x100000 (1MB). 
 *      The .data (initialised static data) and the .bss (uninitialised static data) should be next, 
 *      and each should be page-aligned (ALIGN(4096)).
 *      Linux GCC also adds in an extra data section: .rodata. 
 *      This is for read-only initialised data, such as constants. 
 *      For simplicity we simply bundle this in with the .data section.
 */

ENTRY(start)
SECTIONS
{
	PROVIDE( kern_start = 0xC0100000);
	. = 0x100000; 
	.init.text : 
	{
		*(.init.text)
		. = ALIGN(4096);
	}
	.init.data : 
	{
		*(.init.data)
		. = ALIGN(4096);
	}

	. += 0xC0000000;
	.text : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss : AT(ADDR(.bss) - 0xC0000000)
	{
		*(.bss)
		. = ALIGN(4096);
	}
	.stab : AT(ADDR(.stab) - 0xC0000000)
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr : AT(ADDR(.stabstr) - 0xC0000000)
	{
		*(.stabstr)
	 	. = ALIGN(4096);
	}
	PROVIDE( kern_end = . );
	
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}

