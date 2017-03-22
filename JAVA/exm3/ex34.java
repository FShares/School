package exm3;
/**
 * Created by Administrator on 3/8/2017.
 */
public class ex34{
    //编写一个类，使该类中具有不同访问权限的成员，将这个类存放在包中，在另一个包内编写第二个类，在此类中编写一个方法，在该方法中操作第一个类的成员。
    //第一个类：A
    //本类中操作第一个类
    public static void main(String[] args) {
        int r = 22, result;
        A a = new A();
        result = a.method1(r);       //调用A类中的method1方法
        a.origin="NewStr";           //操作A类中的orign变量
    }
}
