/*
1��ʹ��ָ�뽻����������
2������ʵ��һ���ṹ�����飬��������Ԫ�������
3��ʹ��malloc()����ά���鶯̬����洢�ռ䣬��Ϊ���鸳ֵ���������Ԫ�ء�
�����飬��������׼��
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
 * �ڶ���
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
 * ������
 * ʹ��malloc()����ά���鶯̬����洢�ռ䣬��Ϊ���鸳ֵ���������Ԫ�ء�
 */

/*��̬�ڴ�������ͷź���*/
void *malloc(unsigned int size);
void *calloc(unsigned int num, unsigned int size);
void *realloc(void *p,unsigned int size);
void free(void *p);
/*
malloc()�����ɹ������������ٿռ��׵�ַ��ʧ��:���ؿ�ָ�룻���ܣ���ϵͳ����size�ֽڶѵĿռ䣻
calloc()�ɹ������������ٿռ��׵�ַ��ʧ��:���ؿ�ָ�룻���ܣ���������ϵͳ����num��size�ֽڶѵĿռ䣻
realloc()�ɹ������������ٿռ��׵�ַ��ʧ��:���ؿ�ָ�룻���ܣ���pָ��Ŀռ��Ϊ��size�ֽڶѵĿռ䣻
free()û�з���ֵ���ͷ�pָ��Ķѿռ䣻
*/
//=====================
void main(void)
{
    /*
        int *a;

        int n;

        n = 10;

        a =(int *)malloc(sizeof(int)*n);            //��̬������10�����͵��ڴ棬��������ռ���ʼ��ַת��Ϊ���͵�ַ����ָ��a

        a[5] = 100;                            //  a[5]�൱��*(a+5), �����׵�ַ�������5�������ͣ��ڴ�

        free(a);                                        //�ͷ�a��ָ���ڴ���
    */

//��֪����ַ�ͱ������͵�����£�a[i]��ͬ��*(a+i)�������׵�ַ��ʼ����i����֪���͵�����Ԫ�ء��������ڴ溯��ԭ��Ϊvoid *malloc(usigned size)��
//��void *calloc(unsigned n, unsign size);���ǰ�����<stdlib.h>�С�
//���������ж���һ��ǰ�߷���size���ֽڴ�С�������ռ䣬���߷���n��size�ֽڵ������ռ䡣���Ǻ��߷�����ڴ��ʼ��Ϊ0����ǰ��û�У�
//�����ı�һ���ѷ����ַ���ڴ����Ĵ�С�����ú���void *realloc(void *p, unsign size)��
//�⼸����������void ָ�����ͣ���ֵ����������ָ��ʱ���辭������ת����ϵͳһ���ڱ���ʱҲ������ʽת����

//===============================================
//===============================================

    int arrLen;  // ���鳤��
    int *array;  // ����ָ��
    int i;  // �����±�
    printf("�������鳤�ȣ�");
    scanf("%d", &arrLen);

    // ��̬�����ڴ�ռ䣬���ʧ�ܾ��˳�����
    array = (int*)malloc( arrLen*sizeof(int) );
    if(!array)
    {
        printf("��������ʧ�ܣ�\n");
        exit(1);
    }
    // ���ڴ���д������
    for(i=0; i<arrLen; i++)
    {
        array[i] = i+1;
    }

    // ѭ���������Ԫ��
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
