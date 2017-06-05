package cn.njxzc.homework;

/**
 * Created by 1 on 5/3/17.
 */
public class DoWork extends Thread {
//一个线程进行阶乘喝的运算（比如：1！+2！+3！+...+n！），另外一个线程则每隔一段时间读取上个线程的运算结果。
    private int type;
    private static long result = 0;
    private static boolean isOver = false;
    private static long num = 1;
    private final long maxN = 10;
    //最大记到的整数,我测的结果，最多取171就溢出了
    public DoWork(int type) {
        super();
        this.type = type;
    }
    public static void main(String[] args) {
        DoWork work1 = new DoWork(1);
        DoWork work2 = new DoWork(2);
        work1.start();
        work2.start();
    }
    public void run() {
        while (!isOver && type == 1) {// 注意：两个while不能合并
            sumN(maxN);
        }
        while (num <= maxN && type == 2) {
            // 读取结果
            System.out.println("result=" + result + " n=" + num);

            // work1停了，work2还要读最后一次的结果
            if (num >= maxN)
                break;
            try {
                sleep(10);// 小睡一会儿再读
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    // 算阶乘和
    public void sumN(long n) {
        long lastFactorial = 1;
        for (long i = 1; i <= n; i++) {
            this.num = i;// 计数器，记住算到哪个数了
            try {
                sleep(5);// work1也要小小休息，不然太快了，work2都还来不及记
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            result += factorial(i);// 常规算法调用
        }
        isOver = true;
    }

    // 算阶乘,这个是常规算法
    public long factorial(long n) {
        return(n<=1)?1: n * factorial(n - 1);
    }
}