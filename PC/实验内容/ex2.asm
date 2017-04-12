;设有三个字节变量A，B，D，求表达式Y=（2（A+B）+D）/2的值，
;y=(2(2+4)+6)2 = 9
;并将结果存放至内存Y单元中。

DATAS SEGMENT			;数据段开始，DATAS为段名，表示该段地址
A db 2				
B db 4
D db 6	
Y db 1 dup(?)			
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    MOV AL,A				;AL<-A
    ADD AL,B				;AL<-A+B
    SHL AL,1				;算术左移一次，目的操作数AL乘2
    ADD AL,D				;AL<-AL+D
    SHR AL,1				;算术右移一次，目的操作数AL除2
    MOV Y,AL				;Y
    
    MOV AH,4CH
    INT 21H

CODES ENDS
    END START





