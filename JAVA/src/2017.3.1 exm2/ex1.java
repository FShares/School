public class ex1 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int [] a={10,2,33,1,44,23,11,0};
		int max,min,sums,avg;
		min=a[0];		//把第一个值设置为最大值
		max=a[0];		//把第一个值设置为最小值
		for(int i=0;i<a.length;i++)
		{
			if(a[i]<min)
				min=a[i];
			else
			if(a[i]>max) max=a[i];
		}

		System.out.println("最小值为:"+min);
		System.out.println("最大值为:"+max);
		sums=ArraySum(a,0,a.length-1);
		System.out.println("数组合为:"+sums);
		avg=sums/a.length;
		System.out.println("数组平均数为： "+avg);

	}

	static int ArraySum(int a[],int low,int high){
		//二分递归求数组合
		if(low==high) return a[low];
		int mi=(low+high)>>1;
		return ArraySum(a,low,mi)+ArraySum(a,mi+1,high);
	}

}
