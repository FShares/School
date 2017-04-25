package cn.njxzc.homework;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by 1 on 4/19/17.
 */
public class ex2 {
    public static void main(String[] args) {
        //向Set集合中添加“to”、“be”、“or”、“not”、“to”、“be”6个元素，统计输出重复的单词，输出不同的单词。
        Set uniques = new HashSet();
        Set dups = new HashSet();
        System.out.println("原数据：");
        for(int i =0; i<args.length;i++){
            System.out.println(args[i]);
            if(!uniques.add(args[i]))
            {
                dups.add(args[i]);
            }
            uniques.removeAll(dups);
        }
        System.out.println("重复元素："+dups);
        System.out.println("唯一元素："+uniques);
    }
}
