package cn.njxzc.homework;

import java.util.ArrayList;

public class ex1 {

    public static void main(String[] args) {
        //将1-50所有的数字存放到一个List集合中，并将集合中索引的位置是10的对象从集合中移除。
        //System.out.println("Hello World!");
        ArrayList a1 = new ArrayList();
        for(int i=0;i<=50;i++){
            a1.add(i);
        }
        a1.remove(10);
        System.out.println("集合："+a1);
    }
}


