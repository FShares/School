package exm5;

public class User {
/*
 * ���а����û���������������Լ����췽������������2 ������
 * ��ȡ�����ÿ���ķ�������ʾ���޸��û����ķ�����
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
