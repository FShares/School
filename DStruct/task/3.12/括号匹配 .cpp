#include <stdio.h>
#include <malloc.h>   //malloc,realloc
#include <math.h>     //����overflow
#include <process.h>  //exit()
#define S_SIZE 100   //ջ�Ŀռ��С
#define STACKINCREAMENT 10//���ӿռ�
struct SqStack
{
    int *base; //ջ��
    int *top;  //ջ��
    int stacksize;   //ջ��ǰ�Ĵ洢�ռ�
};
int main()
{
    //�Ӻ�������
    void InitStack(SqStack &S);//��ʼ����ջ
    int StackEmpty(SqStack S);//�п�
    void push(SqStack &S,int e);//��ջ
    void pop(SqStack &S,int &e);//��ջ
    //��������ʼ
    SqStack s;//��ʼ����ջ
    InitStack(s);
    char ch[100],*p;
    int e;
    p=ch;
    printf("��һ��������()[]{}�����ű��ʽ:\n");
    gets(ch);
    while(*p)
    {
        switch (*p)
        {
        case '{':
        case '[':
        case '(':
            push(s,*p++);
            break;//ֻҪ�������ž���ջ
        case '}':
        case ']':
        case ')':
            pop(s,e);
            if ((e=='{' && *p=='}') ||(e=='[' && *p==']') || (e=='(' && *p==')'))
                p++;
            else
            {
                printf("���Ų�ƥ��!");
                exit(OVERFLOW);
            }
            break;
        default :
            p++;//�����ַ��ͺ���
        }
    }
    if (StackEmpty(s))
        printf("����ƥ��ɹ�");
    else
        printf("ȱ�������ţ�");
    printf("\n");
}
void InitStack(SqStack &S)
{
    S.base=(int *)malloc(S_SIZE*sizeof(int));
    S.stacksize=S_SIZE;
    S.top=S.base;//��ʼ����ջ
}
int StackEmpty(SqStack S)
{
    if(S.base==S.top)
        return 1;
    else
        return 0;
}
void push(SqStack &S,int e)
{
    //��ջ
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(int *)realloc(S.base,(S.stacksize+STACKINCREAMENT)*sizeof(int));
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREAMENT;
    }
    *(S.top)=e;
    S.top++;
}
void pop(SqStack &S,int &e)
{
    //��ջ
    if(S.base!=S.top)
    {
        S.top--;
        e=*S.top;
    }
}
