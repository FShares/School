;���������ֽڱ���A��B��D������ʽY=��2��A+B��+D��/2��ֵ��
;y=(2(2+4)+6)2 = 9
;�������������ڴ�Y��Ԫ�С�

DATAS SEGMENT			;���ݶο�ʼ��DATASΪ��������ʾ�öε�ַ
A db 2				
B db 4
D db 6	
Y db 1 dup(?)			
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    MOV AL,A				;AL<-A
    ADD AL,B				;AL<-A+B
    SHL AL,1				;��������һ�Σ�Ŀ�Ĳ�����AL��2
    ADD AL,D				;AL<-AL+D
    SHR AL,1				;��������һ�Σ�Ŀ�Ĳ�����AL��2
    MOV Y,AL				;Y
    
    MOV AH,4CH
    INT 21H

CODES ENDS
    END START





