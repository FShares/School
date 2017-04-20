DATA SEGMENT
    ;此处输入数据段代码  
    BUF DW 1234H,2344H,3483H,5600H
    COUNT EQU ($-BUF)/2			;求出数据的个数
    JIEGUO  DW	?				;三个字节中存放结果
DATA ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STAPN	DB	100DUP(?)
TOP		EQU LENGTH STAPN
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATA,SS:STACKS
START:
    ;此处输入代码段代码
    ;循环结构：判断数据段中BUF开始的若干个字节数据是小于6、等于6还是大于6？
    ;分别转向DAYU、DENGYU和XIAOYU三个分支分别进行处理，
    ;把小于、等于和大于的个数分别存入数据段JIEGUO开始的三个字节中。
    MOV AX,STACKS  	;设置堆栈段
    MOV SS,AX
	MOV SP,TOP
	PUSH DS
	SUB AX,AX
	PUSH AX
	
	MOV AX,DATA		;设置数据段
	MOV DS,AX
	
    MOV CX,COUNT    ;数据字数
    LEA BX,BUF   	;BX<-UBF的偏移地址
    MOV AX,[BX]		;AX<-缓冲器取一个娄
    INC BX
    INC BX
    DEC CX			;循环次数减1
    
AGAIN:
	CMP	AX,6			;AX与6比较
	JG	DAYU			;如果大于(>)则跳转
	JE	DENGYU			;如果等于(=)则跳转
	JL  XIAOYU			;如果小于(<)则跳转
	
DAYU:	LOOP AGAIN		;已处理完，比较继续
	MOV JIEGUO,AX
	RET				;返回DOS
    MOV AH,4CH
    INT 21H

DENGYU:	LOOP AGAIN		;已处理完，比较继续
	MOV JIEGUO,AX
	RET				;返回DOS
    MOV AH,4CH
    INT 21H

XIAOYU:	LOOP AGAIN		;已处理完，比较继续
	MOV JIEGUO,AX
	RET				;返回DOS
    MOV AH,4CH
    INT 21H
    
CODES ENDS
    END START
