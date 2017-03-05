#ifndef _EG_2_1_H_
//防止 2-1.h被重复引用
#define _EG_2_1_H_

typedef void List;
typedef void ListNode;

/*
    该方法用于创建并且返回一个空的线性表
*/
List* List_Create();

/*
    该方法用于销毁一个线性表list
*/
void List_Destroy(List* list);

/*
    该方法用于将一个线性表list中的所有元素清空
    使得线性表回到创建时的初始状态
*/
void List_Clear(List* list);

/*
    该方法用于返回一个线性表list中的所有元素个数
*/
int List_Length(List* list);

/*
    该方法用于向一个线性表list的pos位置处插入新元素node
    返回值为1表示插入成功，0表示插入失败
*/
int List_Insert(List* list, ListNode* node, int pos);

/*
    该方法用于获取一个线性表list的pos位置处的元素
    返回值为pos位置处的元素，NULL表示获取失败
*/
ListNode* List_Get(List* list, int pos);

/*
    该方法用于删除一个线性表list的pos位置处的元素
    返回值为被删除的元素，NULL表示删除失败
*/
ListNode* List_Delete(List* list, int pos);

#endif
