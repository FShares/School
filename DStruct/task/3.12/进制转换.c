#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define S_SIZE 100 //栈所占空间
#define STACKINCREAMENT 10 //扩充空间时一次扩充10个字节
typedef struct SqStack
{
    int*base;//栈底
    int*top;//栈顶
    int stacksize;//栈当前的存储空间
}SqStack;
//主函数声明
SqStack * lnitStack();//初始化空栈
int StackEmpty(SqStack *S);//栈空
void GetTop(SqStack *S ,int *e);//获得栈顶元素
void push(SqStack *S,int *e);//进栈
void pop(SqStack *S,int *e);//出栈
void convert(SqStack *S,int N,int n );//十进制转换N进制
void main()
{  
    int  n,N;
    SqStack *s;
    s=lnitStack();//初始化空栈
    printf("输入要转换的十进制数和要转换的进制数：\n");
    printf("如:10,2 \n");
    scanf("%d,%d",&N,&n);
    printf("%d转换为%d进制后为：\n",N,n);
    convert(s,N,n);
}
SqStack * lnitStack()
{   
    SqStack *S;
    S=(SqStack *)malloc(sizeof(SqStack ));
    S->base=(int*)malloc(S_SIZE*sizeof(int));
    S->stacksize=S_SIZE;
    S->top=S->base;//初始化空栈
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
{   //出栈  
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
        if(a > 9)//十六进制时输出字母
        {
                a = a + 55;  
                printf("%c",a);   
        }   
        else    
            printf("%d",a);  
    }  printf("\n"); 
}
