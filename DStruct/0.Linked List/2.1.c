/*
 作业:建立一个有10个数据元素顺序线性表
      实现顺序线性表的 Add Delete Alter Search等alogrithm
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
