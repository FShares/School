package cn.njxzc.homework;

import java.util.ArrayList;

/**
 * Created by 1 on 4/19/17.
 */
public class ex4 {
    public static void main(String[] args) {
        //将ArrayList对象转换为一个数组对象。

        //最终，List转换为Array可以这样处理：

        ArrayList list=new ArrayList();
        list.add("a");
        list.add("b");
        list.add("c");
        System.out.println(list);

        String[] strings = new String[list.size()];
        list.toArray(strings);

        for(int i=0;i<strings.length;i++){
            System.out.println(strings[i]);
        }
        //反过来，如果要将数组转成List怎么办呢？如下：
//        String[] s = {"a","b","c"};
//        List list = java.util.Arrays.asList(s);

    }
}
