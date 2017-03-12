#include "stdlib.h"
#include "stdio.h"

typedef struct Stack
{
    int *base;
    int *top;
    int stacksize;
} SqStack;

void InitStack(SqStack &s)
{
    s.base=(int *)malloc(100*sizeof(int));
    if(!s.base) exit(0);
    s.top=s.base;
    s.stacksize=100;
    return;
}
void Push(SqStack &s,int elem)
{
    if(s.top-s.base>=s.stacksize)
    {
        s.base=(int *)realloc(s.base,(s.stacksize+10)*sizeof(int));
        if(!s.base) exit(0);
        s.top=s.base+s.stacksize;
        s.stacksize+=10;
    }
    *s.top++=elem;
    return;
}

void Pop(SqStack &s,int &backElem)
{
    if(s.top==s.base) return;
    backElem=*--s.top;
    return;
}
int isEmpty(SqStack &s)
{
    if(s.top==s.base)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
int main()
{
    SqStack s;
    int n,d,back;

    InitStack(s);
    while(true)
    {
        printf("\n");
        printf("请输入要转换的数字：");
        scanf("%d",&n);
        printf("请输入要转换成几进制：");
        scanf("%d",&d);
        if(n==0)
        {
            printf("转换完成：0");
            continue;
        }

        while(n)
        {
            Push(s,n%d);
            n=n/d;
        }
        printf("转换完成：");
        if(d==16)
        {
            while(isEmpty(s)==1)
            {
                Pop(s,back);
                if(back>=10)
                {
                    switch (back)
                    {
                    case 10:
                        printf("A");
                        break;
                    case 11:
                        printf("B");
                        break;
                    case 12:
                        printf("C");
                        break;
                    case 13:
                        printf("D");
                        break;
                    case 14:
                        printf("E");
                        break;
                    case 15:
                        printf("F");
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    printf("%d",back);
                }
            }
        }
        else
        {
            while(isEmpty(s)==1)
            {
                Pop(s,back);
                printf("%d",back);
            }
        }

    }
    return 0;
}
