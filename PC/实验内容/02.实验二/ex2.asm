DATA SEGMENT
    ;�˴��������ݶδ���  
    BUF DW 1234H,2344H,3483H,5600H
    COUNT EQU ($-BUF)/2			;������ݵĸ���
    JIEGUO  DW	?				;�����ֽ��д�Ž��
DATA ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STAPN	DB	100DUP(?)
TOP		EQU LENGTH STAPN
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATA,SS:STACKS
START:
    ;�˴��������δ���
    ;ѭ���ṹ���ж����ݶ���BUF��ʼ�����ɸ��ֽ�������С��6������6���Ǵ���6��
    ;�ֱ�ת��DAYU��DENGYU��XIAOYU������֧�ֱ���д���
    ;��С�ڡ����ںʹ��ڵĸ����ֱ�������ݶ�JIEGUO��ʼ�������ֽ��С�
    MOV AX,STACKS  	;���ö�ջ��
    MOV SS,AX
	MOV SP,TOP
	PUSH DS
	SUB AX,AX
	PUSH AX
	
	MOV AX,DATA		;�������ݶ�
	MOV DS,AX
	
    MOV CX,COUNT    ;��������
    LEA BX,BUF   	;BX<-UBF��ƫ�Ƶ�ַ
    MOV AX,[BX]		;AX<-������ȡһ��¦
    INC BX
    INC BX
    DEC CX			;ѭ��������1
    
AGAIN:
	CMP	AX,6			;AX��6�Ƚ�
	JG	DAYU			;�������(>)����ת
	JE	DENGYU			;�������(=)����ת
	JL  XIAOYU			;���С��(<)����ת
	
DAYU:	LOOP AGAIN		;�Ѵ����꣬�Ƚϼ���
	MOV JIEGUO,AX
	RET				;����DOS
    MOV AH,4CH
    INT 21H

DENGYU:	LOOP AGAIN		;�Ѵ����꣬�Ƚϼ���
	MOV JIEGUO,AX
	RET				;����DOS
    MOV AH,4CH
    INT 21H

XIAOYU:	LOOP AGAIN		;�Ѵ����꣬�Ƚϼ���
	MOV JIEGUO,AX
	RET				;����DOS
    MOV AH,4CH
    INT 21H
    
CODES ENDS
    END START
