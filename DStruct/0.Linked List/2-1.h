#ifndef _EG_2_1_H_
//��ֹ 2-1.h���ظ�����
#define _EG_2_1_H_

typedef void List;
typedef void ListNode;

/*
    �÷������ڴ������ҷ���һ���յ����Ա�
*/
List* List_Create();

/*
    �÷�����������һ�����Ա�list
*/
void List_Destroy(List* list);

/*
    �÷������ڽ�һ�����Ա�list�е�����Ԫ�����
    ʹ�����Ա�ص�����ʱ�ĳ�ʼ״̬
*/
void List_Clear(List* list);

/*
    �÷������ڷ���һ�����Ա�list�е�����Ԫ�ظ���
*/
int List_Length(List* list);

/*
    �÷���������һ�����Ա�list��posλ�ô�������Ԫ��node
    ����ֵΪ1��ʾ����ɹ���0��ʾ����ʧ��
*/
int List_Insert(List* list, ListNode* node, int pos);

/*
    �÷������ڻ�ȡһ�����Ա�list��posλ�ô���Ԫ��
    ����ֵΪposλ�ô���Ԫ�أ�NULL��ʾ��ȡʧ��
*/
ListNode* List_Get(List* list, int pos);

/*
    �÷�������ɾ��һ�����Ա�list��posλ�ô���Ԫ��
    ����ֵΪ��ɾ����Ԫ�أ�NULL��ʾɾ��ʧ��
*/
ListNode* List_Delete(List* list, int pos);

#endif
