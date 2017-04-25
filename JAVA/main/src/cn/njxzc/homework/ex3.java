package cn.njxzc.homework;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Created by 1 on 4/19/17.
 */
public class ex3 {
    public static void main(String[] args) {
        //利用映射结构保存由学号和学生姓名所组成的键-值对，比如“201407198”和“张三”，按学号的自然顺序将这些键-值对一一打印出来。
        Map m = new HashMap();
        m.put("20128373","李林");
        m.put("20341234","赵呃");
        m.put("20387421","言档");
        Iterator iter = m.entrySet().iterator();
        while (iter.hasNext()){
            Map.Entry e = (Map.Entry) iter.next();
            System.out.println(e.getKey()+"-"+e.getValue());
        }
    }
}
