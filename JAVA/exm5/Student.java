package exm5;
/*
 * ����һ��student��,���а����û������������Ա𡢳������µ�����
 * �Լ�init()������ʼ�������ԡ�display()������ʾ�����ԡ�modify()�����޸������ȷ�����ʵ�ֲ���������ࡣ  
 * �������student����������Granduate(�о���)��
 * ������ԣ�רҵsubject����ʦadviser��������Ӧ�ĳ�Ա����������������ࡣ
 */
public class Student {
	//�û������������Ա𡢳�������
	protected int sNo;
	protected String sName;
	protected String sSex;
	protected String sBirthDate;
	private String subject; //רҵ
	private String adviser; //��ʦ
	
	protected void init(){
		sNo = 0;
		sName = "������";
		sSex = "��";
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
