; -------------------------------------------------
; 	将 GDT 地址 载入 GDTR
;
; 	hurley 2013/7/26
;
; -------------------------------------------------

[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]  ; 参数存入 eax 寄存器
	lgdt [eax]        ; 加载到 GDTR [修改原先GRUB设置]

	mov ax, 0x10      ; 加载数据段描述符
	mov ds, ax        ; 更新所有可以更新的段寄存器
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 远跳转，0x08是代码段描述符
			  ; 远跳目的是清空流水线并串行化处理器
.flush:
	ret
