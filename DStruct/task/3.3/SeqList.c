#include <stdio.h>
#include <malloc.h>
#include "SeqList.h"

typedef unsigned int TSeqListNode;      //�ɸ���  ���ֵַ ˳��������  ��װ˳�����
typedef struct _tag_SeqList             //��װ˳���
{
    int capacity;                       //˳�������
    int length;                         //˳���ǰ����
    TSeqListNode* node;                 //˳�����ָ��
} TSeqList;

/*****************************************************************************
* ˳�����
* �����ɹ�����˳���ͷָ��
* ����ʧ�ܷ���NULL
******************************************************************************/
SeqList* SeqList_Create(int capacity) // O(1)
{
    TSeqList* ret = NULL;

    if( capacity >= 0 )
    {
        // һ��������˳����ͷ�ռ估˳������ݿռ䣬˳�������������˳����ͷ�ռ�
        //                     ( ͷTSeqList ��С )+ ( ����*����  ��С )
        ret = (TSeqList*)malloc(sizeof(TSeqList) + sizeof(TSeqListNode) * capacity);
    }

    if( ret != NULL )
    {
        ret->capacity = capacity;
        ret->length = 0;                        //�����ʼ��ʱΪ0
        ret->node = (TSeqListNode*)(ret + 1);   //�� nodeָ�� β���� capacity;      ���ñ�ͷ�������������ϵ���õ�������ָ��
    }

    return ret;     //ret   �� capactiy, length,*node;
}
/*****************************************************************************
* ˳�������
* û�з���ֵ�����ͷ������������ͷ�˳���ͷ�����˳���ָ�����
******************************************************************************/
void SeqList_Destroy(SeqList* list) // O(1)
{

    TSeqList* sList = (TSeqList*)list;
    TSeqListNode* pList = sList->node;
    free(pList);                             // �ͷ�˳������ݿռ�
    free(list);                              // �ͷ�˳����ͷ�ռ�
    list = NULL;
}
/*****************************************************************************
* ˳�������
* û�з���ֵ��ֱ�ӽ�˳��������㣬����ԭ�����ݵĴ���
******************************************************************************/
void SeqList_Clear(SeqList* list) // O(1)
{
    TSeqList* sList = (TSeqList*)list;  //ǿ��ת��

    if( sList != NULL )
    {
        sList->length = 0;
    }
}
/*******************************************************************
* ����˳���ĳ���
* ����-1��ʾ��ȡʧ��
* ���طǸ�����ʾ��ȡ�ɹ�
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
* ����˳��������
* ����-1��ʾ��ȡʧ��
* ���طǸ�����ʾ��ȡ�ɹ�
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
* ˳����������
* ����0��ʾ����ʧ��
* ����1��ʾ����ɹ�
********************************************************************/
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos) // O(n)
{
    TSeqList* sList = (TSeqList*)list;

    // 1. �ж����Ա��Ƿ�Ϸ�
    int ret = (sList != NULL);              //sList�Ƿ�����ڴ����е�ַ
    int i = 0;

    // 2. �жϲ���λ���Ƿ�Ϸ�
    ret = ret && (sList->length + 1 <= sList->capacity);
    ret = ret && (0 <= pos);

    if( ret )
    {
        if( pos >= sList->length )
        {
            pos = sList->length;
        }

        // 3. �����һ��Ԫ�ؿ�ʼ����pos��λ��
        //    �ֱ����Ƕ�����ƶ�һ��λ��
        for(i=sList->length; i>pos; i--)
        {
            sList->node[i] = sList->node[i-1];
        }

        // 4. ����Ԫ�ز���
        sList->node[i] = (TSeqListNode)node;

        // 5. ���ȼ�1
        sList->length++;
    }

    return ret;
}
/*******************************************************************
* ��ȡ˳�����
* ����NULL��ʾ��ȡʧ��
* ���ط�NULL��ʾ��ȡ�ɹ�
********************************************************************/
SeqListNode* SeqList_Get(SeqList* list, int pos) // O(1)
{
    TSeqList* sList = (TSeqList*)list;
    SeqListNode* ret = NULL;
    // 1. �ж����Ա��Ƿ�Ϸ�
    // 2. �ж�λ���Ƿ�Ϸ�
    if( (sList != NULL) && (0 <= pos) && (pos < sList->length) )
    {
        // 3. ��ȡԪ��
        ret = (SeqListNode*)(sList->node[pos]);
    }

    return ret;
}

/*******************************************************************
* ɾ��˳�����
* ����NULL��ʾɾ��ʧ��
* ���ط�NULL��ʾɾ���ɹ�
********************************************************************/
SeqListNode* SeqList_Delete(SeqList* list, int pos) // O(n)
{
    TSeqList* sList = (TSeqList*)list;
    SeqListNode* ret = SeqList_Get(list, pos);
    int i = 0;

    // 1. �ж����Ա��Ƿ�Ϸ�
    // 2. �ж�ɾ��λ���Ƿ�Ϸ�
    if( ret != NULL && (0 <= pos) && (pos< sList->length))
    {
        // 3. ȡ��ɾ��Ԫ��
       // ret = sList->node[pos];

        // 4. ��ɾ��λ��pos���Ԫ�طֱ���ǰ�ƶ�һ��λ��
        for(i=pos+1; i<sList->length; i++)
        {
            sList->node[i-1] = sList->node[i];
        }

        // 5. ���ȼ�1
        sList->length--;
    }

    return ret;
}


/*******************************************************************
* ˳����������
* �޷���ֵ
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
* ɾ����i ��k ˳�����
********************************************************************/
//������˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨Ҫ��sС��t��������Ԫ�ء�
//���ҵ�ֵ �� i �ĵ�һ��Ԫ�أ����ҵ�ֵ<k �ĵ�һ��Ԫ�أ�
//Ȼ�󽫺����Ԫ��ǰ�ƣ����ɾ��Ԫ�ص�λ�á�
SeqListNode* SeqList_Delete_I_to_K(SeqList* list, int i, int k)        // O(n)
{
    TSeqList* L = (TSeqList*)list;
    //ɾ��˳���L��ֵ�ڸ���ֵs��t֮�䣨Ҫ��s<t��������Ԫ��
    int j;
    //���Ա�Ϊ�ջ�s��t���Ϸ�
    if (L->length!=0 && i<=k)
    {
        for(j=i+k;j<=L->length;j++){
            L->node[j-k-1]=L->node[j-1];
        }
        L->length-=k;
    }
    return NULL;
}

