DATAS SEGMENT
BUF DB 1H,6H,41H,3H,5H,7H
COUNT EQU $-BUF		;��BUF�ĳ���
JIEGUO DB 0H,0H,0H	;����3���ֽڿռ�
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
;ѭ���ṹ���ж����ݶ���BUF��ʼ�����ɸ��ֽ�������С��6������6���Ǵ���6��
;�ֱ�ת��DAYU��DENGYU��XIAOYU������֧�ֱ���д���
;��С�ڡ����ںʹ��ڵĸ����ֱ�������ݶ�JIEGUO��ʼ�������ֽ��С�
    MOV AX,DATAS
    MOV DS,AX    
    MOV CX,COUNT
    MOV BX,00H;���BUF���±�
NEXT:MOV AL,BUF[BX]
	CMP AL,06H
	JC DAYU;С��6
	JZ DENGYU;����
	JNC XIAOYU;����	
DAYU: MOV SI,00;С��
	JMP more
DENGYU:MOV SI,01 ;����
	JMP more
XIAOYU:MOV SI,02 ;����

more: INC BYTE PTR JIEGUO[SI] 
	INC BX
	LOOP NEXT   
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

