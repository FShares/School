/*
1、使用指针交换两个数；
2、定义实现一个结构体数组，并将数组元素输出；
3、使用malloc()函数维数组动态分配存储空间，并为数组赋值和输出数组元素。
明早检查，请大家做好准备
2/22/2017
*/
#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void main1(void)
{

    int a =10,b=20;
    swap(&a,&b);
    printf("%d,%d",a,b);
}

/*
 * 第二题
 */

struct stu
{
    int num;
    char *name;
    char sex;
    float score;
} boy[5]=
{
    {101,"Zhou ping",'M',45},
    {102,"Zhang ping",'M',62.5},
    {103,"Liou fang",'F',92.5},
    {104,"Cheng ling",'F',87},
    {105,"Wang ming",'M',58}
};
void main2(void)
{
    struct stu *ps;
    printf("No\tName\t\t\tSex\tScore\t\n");
    for(ps=boy; ps<boy+5; ps++)
        printf("%d\t%s\t\t%c\t%f\t\n",ps->num,ps->name,ps->sex,ps->score);
}


/*
 * 第三题
 * 使用malloc()函数维数组动态分配存储空间，并为数组赋值和输出数组元素。
 */

/*动态内存分配与释放函数*/
void *malloc(unsigned int size);
void *calloc(unsigned int num, unsigned int size);
void *realloc(void *p,unsigned int size);
void free(void *p);
/*
malloc()函数成功：返回所开辟空间首地址；失败:返回空指针；功能：向系统申请size字节堆的空间；
calloc()成功：返回所开辟空间首地址；失败:返回空指针；功能：按类型向系统申请num个size字节堆的空间；
realloc()成功：返回所开辟空间首地址；失败:返回空指针；功能：将p指向的空间变为个size字节堆的空间；
free()没有返回值，释放p指向的堆空间；
*/
//=====================
void main(void)
{
    /*
        int *a;

        int n;

        n = 10;

        a =(int *)malloc(sizeof(int)*n);            //动态分配存放10个整型的内存，将所分配空间起始地址转换为整型地址赋给指针a

        a[5] = 100;                            //  a[5]相当于*(a+5), 即从首地址向后跳过5个（整型）内存

        free(a);                                        //释放a所指的内存区
    */

//在知道地址和变量类型的情况下，a[i]等同于*(a+i)，即从首地址开始跳过i个已知类型的数据元素。这两个内存函数原型为void *malloc(usigned size)；
//和void *calloc(unsigned n, unsign size);它们包含在<stdlib.h>中。
//两者区别有二：一是前者分配size个字节大小的连续空间，后者分配n个size字节的连续空间。二是后者分配的内存初始化为0；而前者没有；
//如果想改变一个已分配地址的内存区的大小可以用函数void *realloc(void *p, unsign size)。
//这几个函数返回void 指针类型，赋值给其他类型指针时，需经过类型转换，系统一般在编译时也进行隐式转换。

//===============================================
//===============================================

    int arrLen;  // 数组长度
    int *array;  // 数组指针
    int i;  // 数组下标
    printf("输入数组长度：");
    scanf("%d", &arrLen);

    // 动态分配内存空间，如果失败就退出程序
    array = (int*)malloc( arrLen*sizeof(int) );
    if(!array)
    {
        printf("创建数组失败！\n");
        exit(1);
    }
    // 向内存中写入数据
    for(i=0; i<arrLen; i++)
    {
        array[i] = i+1;
    }

    // 循环输出数组元素
    for(i=0; i<arrLen; i++)
    {
        printf("%d  ", array[i]);
    }

    printf("\n");
    free(array);

    system("pause");
    return 0;

}
//http://www.voidcn.com/blog/zhangyongfeiyong/article/p-6363442.html
