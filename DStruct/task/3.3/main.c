/*
1. 试写出在顺序存储结构下逆转线性表的算法，要求使用最小的附加空间。
2. 从顺序存储结构的线性表a中删除第i个元素起的k个元素。
3. 试写出逆转线性单链表的算法。
4. 已知线性表中的元素非递减有序排列，并以带头结点的单链表作存储结构。试写一高效的算法，删除表中所有值相同的多余元素。
*/

#include <stdio.h>
#include <malloc.h>
typedef void SeqList;
typedef void SeqListNode;

typedef unsigned int TSeqListNode;      //可复用  存地址值 顺序表的类型
typedef struct _tag_SeqList
{
    int capacity;                   //最大容量
    int length;
    TSeqListNode* node;
} TSeqList;

SeqList * SeqList_Create(int capacity)      //O(n)
{
    TSeqList *ret = NULL;
    if (capacity>=0)
    {
        ret= (TSeqList*)malloc(sizeof(TSeqList)+sizeof(TSeqListNode)*capacity);
    }
    if(ret!=NULL)
    {
        ret->capacity=capacity;
        ret->length=0;
        ret->node=(TSeqListNode*)(ret+1);
    }
    return ret;
}
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos) // O(n)
{
    TSeqList* sList = (TSeqList*)list;

    // 1. 判断线性表是否合法
    int ret = (sList != NULL);              //sList是否存在内存中有地址
    int i = 0;

    // 2. 判断插入位置是否合法
    ret = ret && (sList->length + 1 <= sList->capacity);
    ret = ret && (0 <= pos);

    if( ret )
    {
        if( pos >= sList->length )
        {
            pos = sList->length;
        }

        // 3. 从最后一个元素开始到第pos个位置
        //    分别将他们都向后移动一个位置
        for(i=sList->length; i>pos; i--)
        {
            sList->node[i] = sList->node[i-1];
        }

        // 4. 将新元素插入
        sList->node[i] = (TSeqListNode)node;

        // 5. 长度加1
        sList->length++;
    }

    return ret;
}
SeqListNode* SeqList_Get(SeqList* list, int pos) // O(1)
{
    TSeqList* sList = (TSeqList*)list;
    SeqListNode* ret = NULL;
    // 1. 判断线性表是否合法
    // 2. 判断位置是否合法
    if( (sList != NULL) && (0 <= pos) && (pos < sList->length) )
    {
        // 3. 获取元素
        ret = (SeqListNode*)(sList->node[pos]);
    }

    return ret;
}

/*******************************************************************
* 删除顺序表结点
* 返回NULL表示删除失败
* 返回非NULL表示删除成功
********************************************************************/
SeqListNode* SeqList_Delete(SeqList* list, int pos) // O(n)
{
    TSeqList* sList = (TSeqList*)list;
    SeqListNode* ret = SeqList_Get(list, pos);
    int i = 0;

    // 1. 判断线性表是否合法
    // 2. 判断删除位置是否合法
    if( ret != NULL && (0 <= pos) && (pos< sList->length))
    {
        // 3. 取出删除元素
        // ret = sList->node[pos];

        // 4. 把删除位置pos后的元素分别向前移动一个位置
        for(i=pos+1; i<sList->length; i++)
        {
            sList->node[i-1] = sList->node[i];
        }

        // 5. 长度减1
        sList->length--;
    }

    return ret;
}

/*******************************************************************
* 删除从i 至k 顺序表结点
********************************************************************/
//从有序顺序表中删除其值在给定值s与t之间（要求s小于t）的所有元素。
//先找到值 ≥ i 的第一个元素，再找到值<k 的第一个元素，
//然后将后面的元素前移，填补被删除元素的位置。
SeqListNode* SeqList_Delete_I_to_K(SeqList* a, int i, int k)        // O(n)
{
    TSeqList* L = (TSeqList*)a;
    //删除顺序表L中值在给定值s与t之间（要求s<t）的所有元素
    int j;
    //线性表为空或s、t不合法
    if (L->length!=0 && i<=k)
    {
        for(j=i+k;j<=L->length;j++){
            L->node[j-k-1]=L->node[j-1];
        }
        L->length-=k;
    }
}

int SeqList_Length(SeqList* list) // O(1)
{
    TSeqList* sList = (TSeqList*)list;
    int ret = -1;

    if( sList != NULL )
    {
        ret = sList->length;
    }

    return ret;
}
/*****************************************************************************
* 顺序表销毁
* 没有返回值，先释放数据区，再释放顺序表头，最后将顺序表指针清空
******************************************************************************/
void SeqList_Destroy(SeqList* list)
{
    TSeqList* sList = (TSeqList*)list;
    TSeqListNode* pList = sList->node;
    free(pList);                             // 释放顺序表数据空间
    free(list);                              // 释放顺序表表头空间
    list = NULL;
}

/*******************************************************************
* 顺序表逆序操作
* 无返回值
********************************************************************/
void SeqList_Reverse(SeqList* list)                      //O(n)
{
    int index = 0;
    int length = SeqList_Length(list);

    if(length > 1)
    {
        TSeqList* sList = (TSeqList*)list;

        for(index = 0; index < length - 1 - index; index++)
        {
            TSeqListNode* swap = (TSeqListNode*)(sList->node[index]);
            sList->node[index] = sList->node[length-1-index];
            sList->node[length-1-index] = (TSeqListNode)swap;
        }
    }
}

void main()
{
    SeqList* list = SeqList_Create(5);
    int i = 0;
    int j = 1;
    int k = 2;
    int x = 3;
    int y = 4;
    int z = 5;
    int index = 0;

    SeqList_Insert(list, &i, 0);
    SeqList_Insert(list, &j, 0);
    SeqList_Insert(list, &k, 0);
    SeqList_Insert(list, &x, 0);
    SeqList_Insert(list, &y, 0);
    SeqList_Insert(list, &z, 0);

    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);

        printf("%d ", *p);
    }
    /*
    * 第一题  链表反转
    */
    SeqList_Reverse(list);
    printf("\nReverse:");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    /*
     * 第二题
     * 从顺序存储结构的线性表a中删除第i个元素起的k个元素。
     */

    SeqList_Delete_I_to_K(list,1,4);
    printf("\nDell 1--> 4: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    printf("\n删除链表元素: ");
    while(SeqList_Length(list)>0)
    {
        int* p = (int*)SeqList_Delete(list,0);
        printf("%d ", *p);
    }
    SeqList_Destroy(list);




    /*
     * 第三题
     * 试写出逆转线性单链表的算法。
     */


    /*
     * 第三题
     * 已知线性表中的元素非递减有序排列，并以带头结点的单链表作存储结构。试写一高效的算法，删除表中所有值相同的多余元素。
     */

}
