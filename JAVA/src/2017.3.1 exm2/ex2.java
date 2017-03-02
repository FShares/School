import java.util.Scanner;
public class ex2 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		System.out.print("请输入一个小数:");
		double input = new Scanner(System.in).nextDouble();
		String[] ary = String.valueOf(input).split("\\.");
		System.out.println("整数部分: " + ary[0]);
		System.out.println("小数部分: " + ary[1]);
	}

}
