#include<stdio.h>
#include<stdlib.h>

#define size 8

typedef struct
{
    int lujing;     //�����ά�����ͼ��ֵ
    int flage;      //�ж�������Ƿ��߹�
    int x;
    int y;
} Element;     //�����ͼÿ������Ϣ�Ľṹ��

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
    printf("��ӡ��ά�����Թ���ͼ:\n");
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
    p->e_elem = elem[0][0];             //ջ��Ԫ��Ϊ���Ͻǵ�һ������Ԫ��
    p->e_elem.flage = 1;             //��flage��Ϊ1��ʾ�Ѿ��߹��ˣ�����������
    p->next = top;
    top = p;
    while(top->e_elem.x != (size-1) || top->e_elem.y != (size-1))
    {
        //�ұ�
        if((top->e_elem.y)+1<size && elem[top->e_elem.x][(top->e_elem.y)+1].lujing == 0 && elem[top->e_elem.x][top->e_elem.y+1].flage == 0)
        {
            elem[top->e_elem.x][top->e_elem.y+1].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x][top->e_elem.y+1];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);//�����ã���ɾ
        }
        //�±�
        else if(top->e_elem.x+1 < size && elem[top->e_elem.x+1][top->e_elem.y].lujing == 0 && elem[top->e_elem.x+1][top->e_elem.y].flage == 0)
        {
            elem[top->e_elem.x+1][top->e_elem.y].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x+1][top->e_elem.y];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //���
        else if(top->e_elem.y-1 > 0 && elem[top->e_elem.x][top->e_elem.y-1].lujing == 0 && elem[top->e_elem.x][top->e_elem.y-1].flage == 0)
        {
            elem[top->e_elem.x][top->e_elem.y-1].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x][top->e_elem.y-1];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //�ϱ�
        else if(top->e_elem.x-1 > 0 && elem[top->e_elem.x-1][top->e_elem.y].lujing == 0 && elem[top->e_elem.x-1][top->e_elem.y].flage == 0)
        {
            elem[top->e_elem.x-1][top->e_elem.y].flage = 1;
            p = (Stack_node *)malloc(sizeof(Stack_node));
            p->e_elem = elem[top->e_elem.x-1][top->e_elem.y];
            p->next = top;
            top = p;
            printf("[%d][%d] in.\n",p->e_elem.x,p->e_elem.y);
        }
        //��û�У����ջ
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
    printf("·��������ʾΪ:\n");
    //��Ϊ����ջ��������˳��ջ�洢������ʾ��Ҳ����β�巨����������ָ�뱣��ͷ
    while(head->next != NULL)
    {
        printf("����Ϊ:");
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

    top = (Stack_node *)malloc(sizeof(Stack_node));   //��ʼ��ջ��
    top->next = NULL;

    top = pass_maze(top,elem);
    print_luxian(top);
}
