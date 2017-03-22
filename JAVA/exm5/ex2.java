package exm5;

import java.util.Scanner;

/*
 *（1）创建Rectangle类，添加属性width、height；  
 *（2）在Rectangle类中添加两种方法计算矩形的周长和面积； 
 *（3）编程利用Rectangle输出一个矩形的周长和面积
 */
public class ex2 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		System.out.println("请输入宽和高：");
		Scanner sc=new Scanner(System.in);
		double width = sc.nextDouble();
		double height = sc.nextDouble();
		
		//创建 re 对象
		Rectangle re = new Rectangle();
		//调用 re 中的 求周长与面积方法
		double area = re.getArea(width, height);
		double length = re.getLength(width, height);
		
		//输出结果
		System.out.println("面积是"+area);
		System.out.println("周长是"+length);
	}

}
