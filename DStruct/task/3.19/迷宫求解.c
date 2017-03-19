#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4       /* 迷宫规模 */
#define NUM (N+2) /* 生成迷宫用*/
int maze[NUM][NUM]; /* 迷宫数据 */
/*
 用法:
 结构体定义 typedef struct {int i} ele;
 函数定义 void func(ele *e) {e->i = 0}
 调用函数 func(&e); print(e.i);
 */
typedef struct {
    int x;
    int y;
    int di;
} pos;
typedef struct {
    pos e[N*N];
    int top;
} SqStack;
/********* 栈操作 *********/
void initStack(SqStack *S) {
    S->top = -1;
}
void push(SqStack *S, pos e) {
    S->top++;
    S->e[S->top] = e;
}
void pop(SqStack *S) {
    S->top--;
}
void getTop(SqStack *S, pos *e) {
    *e = S->e[S->top];
}
int isEmpty(SqStack *S) {
    if (S->top == -1) {
        return 1;
    } else {
        return 0;
    }
}
/********** 其他操作 *********/
void setPos(pos *e, int x, int y) {
    e->x = x;
    e->y = y;
}
void setDi(pos *e, int di) {
    e->di = di;
}
/* 是否是出口 */
int isExit(pos *e) {
    if (e->x == N && e->y == N) {
        return 1;
    } else {
        return 0;
    }
}
/* 标记搜索过的点 */
void markSearch(pos e) {
    maze[e.x][e.y] = 2;
}
/* 标记搜索失败的点 */
void clearMark(pos e) {
    maze[e.x][e.y] = 3;
}
/* 从当前位置是否有下一个可以走的点 */
int nextPass(pos *e) {
    int x,y;
    while(e->di < 4) {
        e->di++;
        switch(e->di) {
            case 1:
                x = e->x;
                y = e->y + 1;
                break;
            case 2:
                x = e->x + 1;
                y = e->y;
                break;
            case 3:
                x = e->x;
                y = e->y - 1;
                break;
            case 4:
                x = e->x - 1;
                y = e->y;
                break;
        }
        if (maze[x][y] == 0) {
            e->x = x;
            e->y = y;
            e->di = 0;
            return 1;
        }
    }
    return 0;
}
/************ 迷宫操作 ******/
/* 随机生成迷宫数据 */
void makeMaze() {
    int i, j;
    srand( (unsigned)time(NULL) );
    for (i=0; i<NUM; i++) {
        for (j=0; j<NUM; j++) {
            if (i==0 || i==NUM-1 || j==0 || j==NUM-1) {
                maze[i][j] = 1;
            } else {
                maze[i][j] = rand()%2;
            }
        }
    }
    maze[1][1] = maze[NUM-2][NUM-2] = 0; /* 起点和终点 */
}
/* 打印迷宫 */
void printMaze() {
    int i, j;
    printf("the maze:\n");
    for (i=0; i<NUM; i++) {
        for (j=0; j<NUM; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}
/* 打印路径 */
void printPath(SqStack S) {
    int i;
    printf("\nthe available path:\n");
    for (i = 0; i < S.top; i++) {
        printf("(%d, %d) -> ", S.e[i].x, S.e[i].y);
    }
    printf("(%d, %d)\n", S.e[i].x, S.e[i].y);
}
/* 搜索迷宫 */
int searchMaze() {
    SqStack S;
    pos e;
    initStack(&S);
    setPos(&e, 1, 1); setDi(&e, 0); push(&S, e); markSearch(e);
    while(!isEmpty(&S)) {
        getTop(&S, &e); /* 取当前点 */
        if (isExit(&e)) {
            printPath(S);
            return 1;
        }
        if (nextPass(&e)) { /* 如果从当前点可以到达下一个未经过的点 */
            push(&S, e);
            markSearch(e); /* 标记探索过 */
        } else {
            pop(&S);
            clearMark(e);
        }
    }
    return 0;
}
int main(void) {
    makeMaze(); /* 随机生成迷宫 */
    printMaze();
    if (!searchMaze()) {
        printf("\nPity, no available path...\n");
        makeMaze();
    }
}
