package cn.njxzc.homework;

import java.util.Date;
import java.text.SimpleDateFormat;
/**
 * Created by 1 on 5/3/17.
 */
//定义一个Thread子类，并由该类实例化两个线程对象，两个线程都休眠一定时间，然后打印当前时间，两个线程各自运行20次打印后终止。
public class ex6 extends Thread{
    String name;
    public ex6(String str) {
        name = str;
    }
    @Override
    public void run() {
        for (int i = 1; i <= 20; i++) {
            try {
                Thread.sleep((long) (Math.random() * 1000));
                System.out.print("第"+i+" " + name);
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//设置日期格式
                System.out.println(df.format(new Date()));// new Date()为获取当前系统时间
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("DONE!"+name);
    }
    public static void main(String[] args) {
        Thread t1 = new ex6("进程1：");
        Thread t2 = new ex6("进程2：");
        t1.start();
        t2.start();
    }
}