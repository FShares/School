/*
 ��ҵ:����һ����10������Ԫ��˳�����Ա�
      ʵ��˳�����Ա�� Add Delete Alter Search��alogrithm
*/
#include<stdio.h>
void main()
{
    int n,i;
    scanf("%d",&n);
    CreateList(n);
    for( i=0; i<n; i++)
    {
        printf("%d ",i);
    }
}

int CreateList(int N){
    int i=0,arr[N];
    for(i;i<N;i++){
        arr[i]=i;
    }
    return arr[N];
}
void AddData(int a[],int n){

}
