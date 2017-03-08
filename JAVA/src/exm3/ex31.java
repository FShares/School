package exm3;

import java.util.Scanner;
public class ex31 {
    //1+1/2+1/3+...+1/N!;
    private static double factorial(int n) {
        double sum = 0;
        for(int i=1; i<=n; i++)
            sum += 1.0/i;
        return sum;     //返回结果
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please input int Num:");
        int n = scanner.nextInt();
        System.out.println("Result: " + factorial(n));
    }

}
