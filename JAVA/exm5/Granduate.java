package exm5;
/*
 * �������student����������Granduate(�о���)��
 * ������ԣ�רҵsubject����ʦadviser��������Ӧ�ĳ�Ա����������������ࡣ
 */
public class Granduate extends Student{
	private String subject; //רҵ
	private String adviser; //��ʦ
	

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
