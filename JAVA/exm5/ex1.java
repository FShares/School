package exm5;
/*
 * 写出一个类People，并由该类做基类派生出子类Employee和Teacher。
 * 其中People 类具有name、age两个保护成员变量，
 * 分别为String类型、整型，且具
 * 有公有的getAge成员函数，用于返回age变量的值。
 * Employee类具有保护成员变量empno,Teacher类有teano和zc成员变量。
 */
public class ex1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//People p1 = new People();
		Employee e1 = new Employee();		//创建e1对象
		e1.name="呢呢";
		Teacher t1 = new Teacher();
		t1.name="者者";
		t1.age=23;
		System.out.println("Employee name:"+e1.name);
		System.out.println("Employee Age:"+e1.getAge());	//调用e1的父类getAge()方法
		System.out.println("Teacher name:"+t1.name);
		System.out.println("Teacher Age:"+t1.getAge());
	}

}
