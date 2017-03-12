#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define S_SIZE 100 //ջ��ռ�ռ�
#define STACKINCREAMENT 10 //����ռ�ʱһ������10���ֽ�
typedef struct SqStack
{
    int*base;//ջ��
    int*top;//ջ��
    int stacksize;//ջ��ǰ�Ĵ洢�ռ�
}SqStack;
//����������
SqStack * lnitStack();//��ʼ����ջ
int StackEmpty(SqStack *S);//ջ��
void GetTop(SqStack *S ,int *e);//���ջ��Ԫ��
void push(SqStack *S,int *e);//��ջ
void pop(SqStack *S,int *e);//��ջ
void convert(SqStack *S,int N,int n );//ʮ����ת��N����
void main()
{  
    int  n,N;
    SqStack *s;
    s=lnitStack();//��ʼ����ջ
    printf("����Ҫת����ʮ��������Ҫת���Ľ�������\n");
    printf("��:10,2 \n");
    scanf("%d,%d",&N,&n);
    printf("%dת��Ϊ%d���ƺ�Ϊ��\n",N,n);
    convert(s,N,n);
}
SqStack * lnitStack()
{   
    SqStack *S;
    S=(SqStack *)malloc(sizeof(SqStack ));
    S->base=(int*)malloc(S_SIZE*sizeof(int));
    S->stacksize=S_SIZE;
    S->top=S->base;//��ʼ����ջ
    return S;
}
int StackEmpty(SqStack *S)
{
    if(S->base==S->top)
        return 1;
    else 
        return 0;
}
void GetTop(SqStack *S ,int *e)
{
    *e=*(S->top-1);
}
void push(SqStack *S,int *e)
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base = (int *)realloc(S->base,(S->stacksize+STACKINCREAMENT)*sizeof(int));   
        S->base += S->stacksize;
        S->top = S->base;   
        S->stacksize += STACKINCREAMENT;  
    }  
    *(S->top)=*e;
    S->top++;
}
void pop(SqStack *S,int *e) 
{   //��ջ  
    if(S->base != S->top)  
    {   
        S->top--;
        *e=*S->top;  
    } 
}  
void convert(SqStack *S,int N,int n) 
{
    int a;
 
    lnitStack();  
    do  
    {  
        a=N%n;
        push(S,&a);   
        N = N/n;  
    }
    while(N != 0);  
  
    while(!StackEmpty(S))  
    {   
        pop(S,&a);   
        if(a > 9)//ʮ������ʱ�����ĸ
        {
                a = a + 55;  
                printf("%c",a);   
        }   
        else    
            printf("%d",a);  
    }  printf("\n"); 
}
