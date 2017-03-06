/*
1. 试写出在顺序存储结构下逆转线性表的算法，要求使用最小的附加空间。
2. 从顺序存储结构的线性表a中删除第i个元素起的k个元素。
3. 试写出逆转线性单链表的算法。
4. 已知线性表中的元素非递减有序排列，并以带头结点的单链表作存储结构。试写一高效的算法，删除表中所有值相同的多余元素。
*/

#include <stdio.h>
#include <malloc.h>
#include "SeqList.h"
#include "LinkList.h"
struct Value
{
    LinkListNode header;
    int v;
};

int main(int argc, char *argv[])
{
    /*
     * 初始化线性表
     */
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

    printf("线性表Init: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);

        printf("%d ", *p);
    }


    /*
     * 初始化链表
     */
    LinkList* Llist = LinkList_Create();

    struct Value v1;
    struct Value v2;
    struct Value v3;
    struct Value v4;
    struct Value v5;

    v1.v = 1;
    v2.v = 2;
    v3.v = 2;
    v4.v = 4;
    v5.v = 5;

    printf("\n链表Init: ");
    LinkList_Insert(Llist, (LinkListNode*)&v1, LinkList_Length(Llist));
    LinkList_Insert(Llist, (LinkListNode*)&v2, LinkList_Length(Llist));
    LinkList_Insert(Llist, (LinkListNode*)&v3, LinkList_Length(Llist));
    LinkList_Insert(Llist, (LinkListNode*)&v4, LinkList_Length(Llist));
    LinkList_Insert(Llist, (LinkListNode*)&v5, LinkList_Length(Llist));

    for(index=0; index<LinkList_Length(Llist); index++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(Llist, index);
        printf("%d ", pv->v);
    }



    /*
     * 第一题  链表反转
     */
    SeqList_Reverse(list);
    printf("\n线性表Reverse:");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    /*
     * 第二题
     * 从顺序存储结构的线性表a中删除第i个元素起的k个元素。
     */

    SeqList_Delete_I_to_K(list,1,3);
    printf("\n线性表Dell 1--> 3: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    printf("\n线性表释放并销毁 ");
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

    printf("\n\n链表Reverse:");
    LinkList_Reverse(Llist);
    for(index=0; index<LinkList_Length(Llist); index++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(Llist, index);
        printf("%d ", pv->v);
    }


    /*
     * 第三题
     * 已知线性表中的元素非递减有序排列，并以带头结点的单链表作存储结构。试写一高效的算法，删除表中所有值相同的多余元素。
     */
    printf("\n\n链表Reverse:");
    for(index=0; index<LinkList_Length(Llist); index++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(Llist, index);
        printf("%d ", pv->v);
    }

    deleteDuplication(Llist);
    printf("\n删除重复");





    printf("\n释放 并销毁链表: ");
    while( LinkList_Length(Llist) > 0 )
    {
        struct Value* pv = (struct Value*)LinkList_Delete(Llist, 0);

        printf("%d ", pv->v);
    }

    LinkList_Destroy(Llist);

    return 0;
}
