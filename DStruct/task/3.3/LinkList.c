#include <stdio.h>
#include <malloc.h>
#include "LinkList.h"

typedef struct _tag_LinkList
{
    LinkListNode header;
    int length;
} TLinkList;

LinkList* LinkList_Create() // O(1)
{
    TLinkList* ret = (TLinkList*)malloc(sizeof(TLinkList));

    if( ret != NULL )
    {
        ret->length = 0;
        ret->header.next = NULL;
    }

    return ret;
}

void LinkList_Destroy(LinkList* list) // O(1)
{
    free(list);
}

void LinkList_Clear(LinkList* list) // O(1)
{
    TLinkList* sList = (TLinkList*)list;

    if( sList != NULL )
    {
        sList->length = 0;
        sList->header.next = NULL;
    }
}

int LinkList_Length(LinkList* list) // O(1)
{
    TLinkList* sList = (TLinkList*)list;
    int ret = -1;

    if( sList != NULL )
    {
        ret = sList->length;
    }

    return ret;
}

int LinkList_Insert(LinkList* list, LinkListNode* node, int pos) // O(n)
{
    TLinkList* sList = (TLinkList*)list;
    int ret = (sList != NULL) && (pos >= 0) && (node != NULL);
    int i = 0;

    if( ret )
    {
        LinkListNode* current = (LinkListNode*)sList;

        for(i=0; (i<pos) && (current->next != NULL); i++)
        {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;

        sList->length++;
    }

    return ret;
}

LinkListNode* LinkList_Get(LinkList* list, int pos) // O(n)
{
    TLinkList* sList = (TLinkList*)list;
    LinkListNode* ret = NULL;
    int i = 0;

    if( (sList != NULL) && (0 <= pos) && (pos < sList->length) )
    {
        LinkListNode* current = (LinkListNode*)sList;

        for(i=0; i<pos; i++)
        {
            current = current->next;
        }

        ret = current->next;
    }

    return ret;
}

LinkListNode* LinkList_Delete(LinkList* list, int pos) // O(n)
{
    TLinkList* sList = (TLinkList*)list;
    LinkListNode* ret = NULL;
    int i = 0;

    if( (sList != NULL) && (0 <= pos) && (pos < sList->length) )
    {
        LinkListNode* current = (LinkListNode*)sList;

        for(i=0; i<pos; i++)
        {
            current = current->next;
        }

        ret = current->next;
        current->next = ret->next;

        sList->length--;
    }

    return ret;
}

/*反转链表*/ //3个指针遍历链表

LinkListNode*  LinkList_Reverse(LinkList* list)
{
    TLinkList* sList = (TLinkList*)list;
    //LinkListNode*  ret = (sList != NULL);
    LinkListNode* r = NULL;
    LinkListNode* p = sList->header.next;		//指向第1个结点
    LinkListNode* q = sList->header.next->next;	//指向第2个结点
    sList->header.next = NULL;			//头结点next->NULL

    //开始反转
    while (q != NULL)
    {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }

    sList->header.next = p;

    return NULL;
}


LinkListNode* deleteDuplication( LinkList *head)
{
    int    k=5,i;
    if(k<=0)
        return NULL;
    TLinkList*  p1 = (TLinkList*)head;
    TLinkList*  p2 = (TLinkList*)head;

    for( i=0; i<k-1; i++)
    {
        if(p2==NULL)
            return NULL;
        p2 = p2->header.next;
    }
    if(p2==NULL)
        return NULL;
    while(p2->header.next!=NULL)
    {
        p1 = p1->header.next;
        p2 = p2->header.next;
    }
    return p1;
}

