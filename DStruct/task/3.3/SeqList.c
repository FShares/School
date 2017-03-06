#include <stdio.h>
#include <malloc.h>
#include "SeqList.h"

typedef unsigned int TSeqListNode;      //可复用  存地址值 顺序表的类型  分装顺序表结点
typedef struct _tag_SeqList             //分装顺序表
{
    int capacity;                       //顺序表容量
    int length;                         //顺序表当前长度
    TSeqListNode* node;                 //顺序表结点指针
} TSeqList;

/*****************************************************************************
* 顺序表创建
* 创建成功返回顺序表头指针
* 创建失败返回NULL
******************************************************************************/
SeqList* SeqList_Create(int capacity) // O(1)
{
    TSeqList* ret = NULL;

    if( capacity >= 0 )
    {
        // 一次性申请顺序表表头空间及顺序表数据空间，顺序表数据区紧接顺序表表头空间
        //                     ( 头TSeqList 大小 )+ ( 容量*类型  大小 )
        ret = (TSeqList*)malloc(sizeof(TSeqList) + sizeof(TSeqListNode) * capacity);
    }

    if( ret != NULL )
    {
        ret->capacity = capacity;
        ret->length = 0;                        //链表初始化时为0
        ret->node = (TSeqListNode*)(ret + 1);   //将 node指向 尾容量 capacity;      利用表头与数据区特殊关系，得到数据区指针
    }

    return ret;     //ret   含 capactiy, length,*node;
}
/*****************************************************************************
* 顺序表销毁
* 没有返回值，先释放数据区，再释放顺序表头，最后将顺序表指针清空
******************************************************************************/
void SeqList_Destroy(SeqList* list) // O(1)
{

    TSeqList* sList = (TSeqList*)list;
    TSeqListNode* pList = sList->node;
    free(pList);                             // 释放顺序表数据空间
    free(list);                              // 释放顺序表表头空间
    list = NULL;
}
/*****************************************************************************
* 顺序表清零
* 没有返回值，直接将顺序表长度清零，忽略原有数据的存在
******************************************************************************/
void SeqList_Clear(SeqList* list) // O(1)
{
    TSeqList* sList = (TSeqList*)list;  //强制转换

    if( sList != NULL )
    {
        sList->length = 0;
    }
}
/*******************************************************************
* 返回顺序表的长度
* 返回-1表示获取失败
* 返回非负数表示获取成功
********************************************************************/
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
/*******************************************************************
* 返回顺序表的容量
* 返回-1表示获取失败
* 返回非负数表示获取成功
********************************************************************/
int SeqList_Capacity(SeqList* list) // O(1)
{
    TSeqList* sList = (TSeqList*)list;
    int ret = -1;

    if( sList != NULL )
    {
        ret = sList->capacity;
    }

    return ret;
}
/*******************************************************************
* 顺序表插入运算
* 返回0表示插入失败
* 返回1表示插入成功
********************************************************************/
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
/*******************************************************************
* 获取顺序表结点
* 返回NULL表示获取失败
* 返回非NULL表示获取成功
********************************************************************/
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
* 顺序表逆序操作
* 无返回值
********************************************************************/
void SeqList_Reverse(SeqList* list)             //O(n)
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



/*******************************************************************
* 删除从i 至k 顺序表结点
********************************************************************/
//从有序顺序表中删除其值在给定值s与t之间（要求s小于t）的所有元素。
//先找到值 ≥ i 的第一个元素，再找到值<k 的第一个元素，
//然后将后面的元素前移，填补被删除元素的位置。
SeqListNode* SeqList_Delete_I_to_K(SeqList* list, int i, int k)        // O(n)
{
    TSeqList* L = (TSeqList*)list;
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
    return NULL;
}

