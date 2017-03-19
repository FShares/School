/*
 * 成绩管理系统(SPMS)
 * 最多100个学生
 * SID 学生编号 10位数字
 * CID 班级编号 不超过20 正整数
 * 姓名 <10字母与数学组合 第一个为大写字母
 * 4门课程(语文 数学 英语 编程) 0 < =100 整数
 */

/*
 * Main MENU

Welcome to Student Performance Management System (SPMS).
1 - ADD
2 - REMOVE
3 - Query
4 - Show ranking
5 - Show Statistics
0 - Exit

Select
1 Please enter the SID, CID, name and four scores. Enter 0 to finish.
	Duplicated SID.(重复SID)
2 Please enter SID or name. Enter 0 to finish.
	xx student(s) removed.
3 Please enter SID or name. Enter 0 to finish.
4 Showing the ranklist hurts students' self-esteem. Don't do that.
5 Please enter class ID, 0 for the whole statistics.
 */
#include <stdio.h>
#include <stdlib.h>
#define maxStudnet 100
typedef struct Studnet
{
    int SID;
    char name[10];
    float Chinese, Maths, English, Progamm;
    int *next;
} Students;
Students *head= NULL;

void print_menu(void);
void add(void);
void DQ(int);


int main()
{

    do
    {
        int choice;
        print_menu();
        scanf("%d", &choice);
        switch(choice)
        {
        case 0:
            break;
        case 1:
            add();
            break;
        case 2:
            DQ(1);
            break;
        case 3:
            DQ(2);
            break;
        case 4:
            printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
            break;
        case 5:
            stat();
            break;
        default:
            printf("输入不符合要求请重输！\n");
        }
    }
    while(1);
    return 0;
}
void print_menu(void)
{
    printf("Welcome to Student Performance Management System (SPMS).\n");
    printf("1 - ADD\n");
    printf("2 - REMOVE\n");
    printf("3 - Query\n");
    printf("4 - Show ranking\n");
    printf("5 - Show Statistics\n");
    printf("0 - Exit\n");
}

void add()
{
    FILE *fp;
    char buff[255];

    fp = fopen("Student.txt", "r");
    fscanf(fp, "%s", buff);
    printf("1 : %s\n", buff );

    fgets(buff, 255, (FILE*)fp);
    printf("2: %s\n", buff );

    fgets(buff, 255, (FILE*)fp);
    printf("3: %s\n", buff );
    fclose(fp);
}


/*  合并操作2(删除)和3(查询)  */
void DQ( int isq)
{
    char s[maxStudnet];
    for(;;)
    {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s",s);
        if(strcmp(s,"0")==0)break;
        int r= 0, i;
        for(i=0; i<100; i++)
        {
            /*
            if(!removed[i])
            {
                if(strcmp(sid[i],s)==0||strcmp(name[i],s)==0)
                {
                    if(isq) printf("ds %s %d %s %d %d %d %d %d %.2f\n",rank(i),sid[i],cid[i],name[i],score[i][0],score[i][1],score[i][2],score[i][3],score[i][4]/4.0+EPS);
                    else {removed[i] =1;r++;}
                }
            }
            */
        }
        if(!isq) printf("%d student(s) removed.\n",r);
    }

}
