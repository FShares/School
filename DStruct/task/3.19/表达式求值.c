//栈实现表达式
//思路：此程序的思路是，读取输入的字符串，然后判断每个字符，
//当遇到的是运算符，这时运算符不如栈，接着把栈顶的两个元素
//出栈，然后运算，然后再将得的结果压栈
#include <stdio.h>
#include <stdlib.h>

typedef int SElemType;              // 栈的元素类型

#define STACK_INIT_SIZE 10          // 存储空间初始分配量
#define STACKINCREMENT 2            // 存储空间分配增量

/*
 *顺序栈的结构体
 * */
typedef struct SqStack
{
    SElemType *base;                // 在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;                 // 栈顶指针
    int stacksize;                  // 当前已分配的存储空间，以元素为单位
} SqStack;



/*
 *构造一个栈
 * */
int InitStack(SqStack *S)
{
    // 为栈底分配一个指定大小的存储空间
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if( !(*S).base )
        exit(0);        // 存储分配失败
    (*S).top = (*S).base;   // 栈底与栈顶相同表示一个空栈
    (*S).stacksize = STACK_INIT_SIZE;
    return 1;
}

/*
 *获取栈顶元素
 * */
int GetTop(SqStack S,SElemType *e)
{
    if(S.top > S.base)
    {
        *e = *(S.top-1);    // 栈顶指针的下一个位置为栈顶元素
        return 1;
    }
    else
        return 0;
}

/*
 *入栈（压栈）
 * */
int Push(SqStack *S, SElemType e)
{
    if((*S).top - (*S).base >= (*S).stacksize)   // 栈满，追加存储空间
    {
        (*S).base = (SElemType *)realloc((*S).base,
                                         ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if( !(*S).base )
            exit(0); // 存储分配失败
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *((*S).top)++=e;
    // 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
    return 1;
}


/*
 *出栈
 * */
int Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return 0;
    *e = *--(*S).top;
    // 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
    return 1;
}



/*
 *判断优先级
 * */
SElemType Precede(SElemType t1,SElemType t2)
{
    SElemType f;
    switch(t2)
    {
    case '+':
    case '-':
        if(t1=='('||t1=='#')
            f='<';
        else
            f='>';
        break;
    case '*':
    case '/':
        if(t1=='*'||t1=='/'||t1==')')
            f='>';
        else
            f='<';
        break;
    case '(':
        if(t1==')')
        {
            printf("ERROR1");
            exit(0);
        }
        else
            f='<';
        break;
    case ')':
        switch(t1)
        {
        case '(':
            f='=';
            break;
        case '#':
            printf("ERROR2");
            exit(0);
        default:
            f='>';
        }
        break;
    case '#':
        switch(t1)
        {
        case '#':
            f='=';
            break;
        case '(':
            printf("ERROR3");
            exit(0);
        default:
            f='>';
        }
    }
    return f;
}



/*
 *搜索运算符
 * */
int In(SElemType c)
{
    switch(c)
    {
    case'+':
    case'-':
    case'*':
    case'/':
    case'(':
    case')':
    case'#':
        return 1;
    default:
        return 0;
    }
}

/*
 *运算
 * */
SElemType Operate(SElemType a,SElemType theta,SElemType b)
{
    SElemType c;
    a=a-48;                                             //ASCII值转化为对应的十进制值
    b=b-48;                                             //ASCII值转化为对应的十进制值

    switch(theta)
    {
    case'+':
        c=a+b+48;
        break;
    case'-':
        c=a-b+48;
        break;
    case'*':
        c=a*b+48;
        break;
    case'/':
        c=a/b+48;
    }
    return c;
}

/*
 *比较运算符优先级
 * */
SElemType EvaluateExpression()
{
    SqStack OPTR,OPND;
    SElemType a,b,c,x,theta;
    InitStack(&OPTR);
    Push(&OPTR,'#');
    InitStack(&OPND);
    c=getchar();
    GetTop(OPTR,&x);
    while(c!='#'||x!='#')
    {
        if(In(c)) // 是7种运算符之一
            switch(Precede(x,c))
            {
            case'<':
                Push(&OPTR,c); // 栈顶元素优先权低
                c=getchar();
                break;
            case'=':
                Pop(&OPTR,&x); // 脱括号并接收下一字符
                c=getchar();
                break;
            case'>':
                Pop(&OPTR,&theta); // 退栈并将运算结果入栈
                Pop(&OPND,&b);
                Pop(&OPND,&a);
                Push(&OPND,Operate(a,theta,b));
                break;
            }
        else if(c>='0'&&c<='9') // c是操作数
        {
            Push(&OPND,c);
            c=getchar();
        }
        else    // c是非法字符
        {
            printf("非法字符！！");
            exit(0);
        }

        GetTop(OPTR,&x);
    }
    GetTop(OPND,&x);
    return x;
}

int main()
{
    printf("请输入算术表达式,并以#结束\n");
    printf("例如：3*(7-5)#\n");
    printf("%c",EvaluateExpression());
    return 0;
}
