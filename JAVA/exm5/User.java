package exm5;

public class User {
/*
 * 其中包括用户名、口令等属性以及构造方法（至少重载2 个）。
 * 获取和设置口令的方法，显示和修改用户名的方法等
 */
	private String userName;
	private String userPass;
	User(){
		userName="admin";
		userPass="12345";
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getUserPass() {
		return userPass;
	}
	public void setUserPass(String userPass) {
		this.userPass = userPass;
	}
}
