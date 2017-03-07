import java.util.Scanner;
public class ex2 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
/*
		System.out.print("请输入一个小数:");
		double input = new Scanner(System.in).nextDouble();
		String[] ary = String.valueOf(input).split("\\.");
		System.out.println("整数部分: " + ary[0]);
		System.out.println("小数部分: " + ary[1]);
*/
		Scanner sc = new Scanner(System.in);
		int sysNum = (int) (Math.random() * 100);
		System.out.println("sysNum:" + sysNum);
		System.out.println("请猜数：");
		while (true) {
			int perNum = sc.nextInt();
			if (perNum > sysNum) {
				System.out.println("大了！！");
				//break;
			} else if (perNum < sysNum) {
				System.out.println("小了！！");
				//break;
			} else {
				System.out.println("恭喜你猜对了！！");
				break;
			}
		}

	}
}



