#include<stdio.h>
#include<stdlib.h>

#define size 8

typedef struct
{
    int lujing;     //储存二维数组地图的值
    int flage;      //判断这个点是否走过
    int x;
    int y;
} Element;     //储存地图每个点信息的结构体

typedef struct stack
{
    Element e_elem;
    struct stack *next;
} Stack_node;

/*int maze[size][size] =
{
    {0,0,1,1,1},
    {0,1,1,1,1},
    {0,1,0,0,0},
    {0,0,0,1,0},
    {1,1,1,1,0}
};*/
int maze[size][size] =
{
    {0,0,1,0,0,0,1,0},
    {0,0,1,0,0,0,1,0},
    {0,0,0,0,1,1,0,1},
    {0,1,1,1,0,0,1,0},
    {0,0,0,1,0,0,0,0},
    {0,1,0,0,0,1,0,1},
    {0,1,1,1,1,0,0,1},
    {1,1,0,0,0,1,0,0}
};

void init_maze(Element elem[size][size])
{
    int i,j;
    for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)
        {
            elem[i][j].lujing = maze[i][j];
            elem[i][j].flage = 0;
            elem[i][j].x = i;
            elem[i][j].y = j;
        }
}

void print_maze(Element elem[size][size])
{
    int i,j,k;
    printf("打印二维数组迷宫地图:\n");
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ",elem[i][j].lujing);
        }
        printf("\n");
    }
}

void * pass_maze(Stack_node * top,Element elem[size][size])
{
    Stack_node *p = (Stack_node *)malloc(sizeof(Stack_node));
    p->e_elem = elem[0][0];             //栈顶元素为左上角第一个数组元素
    p->e_elem.flage = 1;             //将flage置为1表示已经走过了，不能再走了
    p->next = top;
    top = p;
    while(top->e_elem.x != (size-1) || top->e_elem.y != (size-1))
    {
        //右边
        if((top->e_elem.y)+1<size && elem[top->e_elem.x][(top->e_elem.y)+1].lujing == 0 && elem[top->e_elem.x][top->e_elem.y+1].flage == 0)
        {
            elem[top->e_elem.x][top->e_elem.y+1].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x][top->e_elem.y+1];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);//调试用，可删
        }
        //下边
        else if(top->e_elem.x+1 < size && elem[top->e_elem.x+1][top->e_elem.y].lujing == 0 && elem[top->e_elem.x+1][top->e_elem.y].flage == 0)
        {
            elem[top->e_elem.x+1][top->e_elem.y].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x+1][top->e_elem.y];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //左边
        else if(top->e_elem.y-1 > 0 && elem[top->e_elem.x][top->e_elem.y-1].lujing == 0 && elem[top->e_elem.x][top->e_elem.y-1].flage == 0)
        {
            elem[top->e_elem.x][top->e_elem.y-1].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x][top->e_elem.y-1];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //上边
        else if(top->e_elem.x-1 > 0 && elem[top->e_elem.x-1][top->e_elem.y].lujing == 0 && elem[top->e_elem.x-1][top->e_elem.y].flage == 0)
        {
            elem[top->e_elem.x-1][top->e_elem.y].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x-1][top->e_elem.y];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //都没有，则出栈
        else
        {
            p = top;
            top = top->next;
            printf("[%d][%d] out.\n",p->e_elem.x,p->e_elem.y);
            free(p);
        }
    }
    return top;
}

void print_luxian(Stack_node * head)
{
    printf("路径倒着显示为:\n");
    //因为是链栈，可以用顺序栈存储，再显示，也可用尾插法，并再声明指针保存头
    while(head->next != NULL)
    {
        printf("坐标为:");
        printf("[%d,%d]\n",head->e_elem.x,head->e_elem.y);
        head = head->next;
    }
}

void main()
{
    Stack_node *top;
    Element elem[size][size];
    init_maze(elem);

    print_maze(elem);

    top = (Stack_node *)malloc(sizeof(Stack_node));   //初始化栈顶
    top->next = NULL;

    top = pass_maze(top,elem);
    print_luxian(top);
}
