package exm3;
import java.util.Arrays;
/**
 * Created by Administrator on 3/8/2017.
 */
// 列举一个简单类，定义学生的基本信息以及课程信息，实现数据的输入输出方法。
public class Student
{
    String name;
    public char sex;
    public int age;
    public String[] course;
    public Student(String s,char c,int i,String []cc)
    {
        name=s;
        sex=c;
        age=i;
        course=cc;         //浅拷贝
        //String[] course=(String[])cc.clone();//深拷贝
    }
    public String ShowINFO()
    {
        String s="姓名："+name+"  性别："+sex+"  年龄："+age+"  课程:"+ Arrays.toString(course);
        return s;              //返回s的值
    }
}