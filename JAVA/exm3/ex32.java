package exm3;
/**
 * Created by ST001 on 2017/3/8.
 */
public class ex32 {
    // 列举一个简单类，定义学生的基本信息以及课程信息，实现数据的输入输出方法。
    public static void main(String[] args) {
        String []c1 ={"化学","数学","物理"};
        String []c2 ={"英语","数学"};
        Student p1 = new Student("张三", '男', 21,c1);
        Student p2 = new Student("李四", '女', 20,c2); //定义对象p2，各个参数分别为：二小，女，28
        System.out.println(p1.ShowINFO());//输出p1的各个属性
        System.out.println(p2.ShowINFO());//输出p2的各个属性
    }
}