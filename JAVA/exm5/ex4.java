package exm5;
/*
 * 定义一个student类,其中包括用户名、姓名、性别、出生年月等属行
 * 以及init()——初始化各属性、display()——显示各属性、modify()——修改姓名等方法。实现并测试这个类。  
 * 从上题的student类中派生出Granduate(研究生)类
 * 添加属性：专业subject、导师adviser。重载相应的成员方法。并测试这个类。
 */
public class ex4 {
	public static void main(String[] args) {

		Student s1 = new Student();
		
		//初始化并显示学生信息
		s1.init();
		s1.disPlay();
		
		System.out.println("修改过后的信息： ");
		//修改信息
		s1.modifyName("张三");
		s1.modifyBirthDate("02/02/1922");
		s1.modifySex("男");
		s1.disPlay();
		
		//创建 Granduate
		Granduate g1 = new Granduate();
		g1.init();
		g1.disPlay();
		
		//修改信息
		g1.setAdviser("Miracle");
		g1.setSubject("计算机");
		
		g1.disPlay("Miracle","计算机");
	}
}
