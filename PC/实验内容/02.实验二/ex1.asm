DATAS SEGMENT
    ;此处输入数据段代码  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    ;分支结构：将CX与DX中较大的一个无符号数放到AX中。
	mov cx,234h  ;十六进制数
	mov dx,785h  ;十六进制数
	cmp cx,dx
	ja lab3 ;如BX>DX ja指令用于无符号数比较，取jump if above，即前者大于后者则转移。
	mov ax,dx
	jmp lab4
	lab3:mov ax,cx
	lab4:mov ah,4ch   
    ;MOV AH,4CH
    INT 21H
CODES ENDS
    END START
