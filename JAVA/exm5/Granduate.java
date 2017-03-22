package exm5;
/*
 * 从上题的student类中派生出Granduate(研究生)类
 * 添加属性：专业subject、导师adviser。重载相应的成员方法。并测试这个类。
 */
public class Granduate extends Student{
	private String subject; //专业
	private String adviser; //导师
	

	public String getSubject() {
		return subject;
	}
	public void setSubject(String subject) {
		this.subject = subject;
	}
	public String getAdviser() {
		return adviser;
	}
	public void setAdviser(String adviser) {
		this.adviser = adviser;
	}
	public void modifyName(String sName) {
		this.sName = sName;
	}

	public void modifySex(String sSex) {
		this.sSex = sSex;
	}

	public void modifyBirthDate(String sBirthDate) {
		this.sBirthDate = sBirthDate;
	}
}
