#include <stdio.h>
#include <malloc.h>   //malloc,realloc
#include <math.h>     //含有overflow
#include <process.h>  //exit()
#define S_SIZE 100   //栈的空间大小
#define STACKINCREAMENT 10//增加空间
struct SqStack
{
    int *base; //栈底
    int *top;  //栈顶
    int stacksize;   //栈当前的存储空间
};
int main()
{
    //子函数声明
    void InitStack(SqStack &S);//初始化空栈
    int StackEmpty(SqStack S);//判空
    void push(SqStack &S,int e);//进栈
    void pop(SqStack &S,int &e);//出栈
    //主函数开始
    SqStack s;//初始化空栈
    InitStack(s);
    char ch[100],*p;
    int e;
    p=ch;
    printf("输一个含义有()[]{}的括号表达式:\n");
    gets(ch);
    while(*p)
    {
        switch (*p)
        {
        case '{':
        case '[':
        case '(':
            push(s,*p++);
            break;//只要是左括号就入栈
        case '}':
        case ']':
        case ')':
            pop(s,e);
            if ((e=='{' && *p=='}') ||(e=='[' && *p==']') || (e=='(' && *p==')'))
                p++;
            else
            {
                printf("括号不匹配!");
                exit(OVERFLOW);
            }
            break;
        default :
            p++;//其他字符就后移
        }
    }
    if (StackEmpty(s))
        printf("括号匹配成功");
    else
        printf("缺少右括号！");
    printf("\n");
}
void InitStack(SqStack &S)
{
    S.base=(int *)malloc(S_SIZE*sizeof(int));
    S.stacksize=S_SIZE;
    S.top=S.base;//初始化空栈
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
    //进栈
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
    //出栈
    if(S.base!=S.top)
    {
        S.top--;
        e=*S.top;
    }
}
