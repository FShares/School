DATAS SEGMENT
    ;�˴��������ݶδ���  
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;��д��������Ļ�����һ����д��ĸ��A����
    MOV DL,'A'
 	MOV AH,02H	;AH<-���ܺŵ���02H
 	INT 21H		;��ʾ->AL�е��ַ�
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


