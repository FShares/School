/*
1. ��д����˳��洢�ṹ����ת���Ա���㷨��Ҫ��ʹ����С�ĸ��ӿռ䡣
2. ��˳��洢�ṹ�����Ա�a��ɾ����i��Ԫ�����k��Ԫ�ء�
3. ��д����ת���Ե�������㷨��
4. ��֪���Ա��е�Ԫ�طǵݼ��������У����Դ�ͷ���ĵ��������洢�ṹ����дһ��Ч���㷨��ɾ����������ֵ��ͬ�Ķ���Ԫ�ء�
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
     * ��ʼ�����Ա�
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

    printf("���Ա�Init: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);

        printf("%d ", *p);
    }


    /*
     * ��ʼ������
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

    printf("\n����Init: ");
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
     * ��һ��  ����ת
     */
    SeqList_Reverse(list);
    printf("\n���Ա�Reverse:");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    /*
     * �ڶ���
     * ��˳��洢�ṹ�����Ա�a��ɾ����i��Ԫ�����k��Ԫ�ء�
     */

    SeqList_Delete_I_to_K(list,1,3);
    printf("\n���Ա�Dell 1--> 3: ");
    for(index=0; index<SeqList_Length(list); index++)
    {
        int* p = (int*)SeqList_Get(list, index);
        printf("%d ", *p);
    }

    printf("\n���Ա��ͷŲ����� ");
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

    printf("\n\n����Reverse:");
    LinkList_Reverse(Llist);
    for(index=0; index<LinkList_Length(Llist); index++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(Llist, index);
        printf("%d ", pv->v);
    }


    /*
     * ������
     * ��֪���Ա��е�Ԫ�طǵݼ��������У����Դ�ͷ���ĵ��������洢�ṹ����дһ��Ч���㷨��ɾ����������ֵ��ͬ�Ķ���Ԫ�ء�
     */
    printf("\n\n����Reverse:");
    for(index=0; index<LinkList_Length(Llist); index++)
    {
        struct Value* pv = (struct Value*)LinkList_Get(Llist, index);
        printf("%d ", pv->v);
    }

    deleteDuplication(Llist);
    printf("\nɾ���ظ�");





    printf("\n�ͷ� ����������: ");
    while( LinkList_Length(Llist) > 0 )
    {
        struct Value* pv = (struct Value*)LinkList_Delete(Llist, 0);

        printf("%d ", pv->v);
    }

    LinkList_Destroy(Llist);

    return 0;
}
