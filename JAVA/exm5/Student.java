package exm5;
/*
 * 定义一个student类,其中包括用户名、姓名、性别、出生年月等属行
 * 以及init()——初始化各属性、display()——显示各属性、modify()——修改姓名等方法。实现并测试这个类。  
 * 从上题的student类中派生出Granduate(研究生)类
 * 添加属性：专业subject、导师adviser。重载相应的成员方法。并测试这个类。
 */
public class Student {
	//用户名、姓名、性别、出生年月
	protected int sNo;
	protected String sName;
	protected String sSex;
	protected String sBirthDate;
	private String subject; //专业
	private String adviser; //导师
	
	protected void init(){
		sNo = 0;
		sName = "测试用";
		sSex = "性";
		sBirthDate = "0/0/0";
	}
	public void disPlay(){
		System.out.println("No: "+this.sNo);
		System.out.println("Name: "+this.sName);
		System.out.println("Sex: "+this.sSex);
		System.out.println("Birth: "+this.sBirthDate);
	}
	
	public void disPlay(String subject, String adviser){
		System.out.println("No: "+this.sNo);
		System.out.println("Name: "+this.sName);
		System.out.println("Sex: "+this.sSex);
		System.out.println("Birth: "+this.sBirthDate);
		System.out.println("Subject: "+subject);
		System.out.println("Adviser: "+adviser);
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
}
