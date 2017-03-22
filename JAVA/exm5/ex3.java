package exm5;
/*
 * 设计一个User类，其中包括用户名、口令等属性以及构造方法（至少重载2 个）。
 * 获取和设置口令的方法，显示和修改用户名的方法等。编写应用程序测试User类。  
 */
public class ex3 {

	public static void main(String[] args) {
		
		User u1 = new User();
		
		 //构造方法中的初始用户名与密码
		System.out.println("u1 name: "+u1.getUserName());
		System.out.println("u1 name: "+u1.getUserPass());
		
		//通过User类中的方法赋值
		u1.setUserName("Administrator");
		u1.setUserPass("Dj#dsEjf832");
		
		//输出

		System.out.println("u1 name: "+u1.getUserName());
		System.out.println("u1 name: "+u1.getUserPass());
	}

}
