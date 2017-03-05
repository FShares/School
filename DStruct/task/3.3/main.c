/*
1. ��д����˳��洢�ṹ����ת���Ա���㷨��Ҫ��ʹ����С�ĸ��ӿռ䡣
2. ��˳��洢�ṹ�����Ա�a��ɾ����i��Ԫ�����k��Ԫ�ء�
3. ��д����ת���Ե�������㷨��
4. ��֪���Ա��е�Ԫ�طǵݼ��������У����Դ�ͷ���ĵ��������洢�ṹ����дһ��Ч���㷨��ɾ����������ֵ��ͬ�Ķ���Ԫ�ء�
*/

#include <stdio.h>
#include <malloc.h>
typedef void SeqList;
typedef void SeqListNode;

typedef unsigned int TSeqListNode;      //�ɸ���  ���ֵַ ˳��������
typedef struct _tag_SeqList
{
    int capacity;                   //�������
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
* ɾ����i ��k ˳�����
********************************************************************/
//������˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨Ҫ��sС��t��������Ԫ�ء�
//���ҵ�ֵ �� i �ĵ�һ��Ԫ�أ����ҵ�ֵ<k �ĵ�һ��Ԫ�أ�
//Ȼ�󽫺����Ԫ��ǰ�ƣ����ɾ��Ԫ�ص�λ�á�
SeqListNode* SeqList_Delete_I_to_K(SeqList* a, int i, int k)        // O(n)
{
    TSeqList* L = (TSeqList*)a;
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
* ˳�������
* û�з���ֵ�����ͷ������������ͷ�˳���ͷ�����˳���ָ�����
******************************************************************************/
void SeqList_Destroy(SeqList* list)
{
    TSeqList* sList = (TSeqList*)list;
    TSeqListNode* pList = sList->node;
    free(pList);                             // �ͷ�˳������ݿռ�
    free(list);                              // �ͷ�˳����ͷ�ռ�
    list = NULL;
}

/*******************************************************************
* ˳����������
* �޷���ֵ
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
    * ��һ��  ����ת
    */
    SeqList_Reverse(list);
    printf("\nReverse:");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    /*
     * �ڶ���
     * ��˳��洢�ṹ�����Ա�a��ɾ����i��Ԫ�����k��Ԫ�ء�
     */

    SeqList_Delete_I_to_K(list,1,4);
    printf("\nDell 1--> 4: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    printf("\nɾ������Ԫ��: ");
    while(SeqList_Length(list)>0)
    {
        int* p = (int*)SeqList_Delete(list,0);
        printf("%d ", *p);
    }
    SeqList_Destroy(list);




    /*
     * ������
     * ��д����ת���Ե�������㷨��
     */


    /*
     * ������
     * ��֪���Ա��е�Ԫ�طǵݼ��������У����Դ�ͷ���ĵ��������洢�ṹ����дһ��Ч���㷨��ɾ����������ֵ��ͬ�Ķ���Ԫ�ء�
     */

}
