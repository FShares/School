#ifndef _SEQLIST_H_
//防止 SeqList.h被重复引用
#define _SEQLIST_H_

typedef void SeqList;
typedef void SeqListNode;

extern SeqList* SeqList_Create(int capacity);

extern void SeqList_Destroy(SeqList* list);

extern void SeqList_Clear(SeqList* list);

extern int SeqList_Length(SeqList* list);

extern int SeqList_Capacity(SeqList* list);

extern int SeqList_Insert(SeqList* list, SeqListNode* node, int pos);

extern SeqListNode* SeqList_Get(SeqList* list, int pos);

extern SeqListNode* SeqList_Delete(SeqList* list, int pos);

extern void SeqList_Reverse(SeqList* list);

extern SeqListNode* SeqList_Delete_I_to_K(SeqList* a, int i, int k);
#endif

