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
    ;�˴��������δ���
    ;��֧�ṹ����CX��DX�нϴ��һ���޷������ŵ�AX�С�
	mov cx,234h  ;ʮ��������
	mov dx,785h  ;ʮ��������
	cmp cx,dx
	ja lab3 ;��BX>DX jaָ�������޷������Ƚϣ�ȡjump if above����ǰ�ߴ��ں�����ת�ơ�
	mov ax,dx
	jmp lab4
	lab3:mov ax,cx
	lab4:mov ah,4ch   
    ;MOV AH,4CH
    INT 21H
CODES ENDS
    END START
