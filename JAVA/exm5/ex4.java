package exm5;
/*
 * ����һ��student��,���а����û������������Ա𡢳������µ�����
 * �Լ�init()������ʼ�������ԡ�display()������ʾ�����ԡ�modify()�����޸������ȷ�����ʵ�ֲ���������ࡣ  
 * �������student����������Granduate(�о���)��
 * ������ԣ�רҵsubject����ʦadviser��������Ӧ�ĳ�Ա����������������ࡣ
 */
public class ex4 {
	public static void main(String[] args) {

		Student s1 = new Student();
		
		//��ʼ������ʾѧ����Ϣ
		s1.init();
		s1.disPlay();
		
		System.out.println("�޸Ĺ������Ϣ�� ");
		//�޸���Ϣ
		s1.modifyName("����");
		s1.modifyBirthDate("02/02/1922");
		s1.modifySex("��");
		s1.disPlay();
		
		//���� Granduate
		Granduate g1 = new Granduate();
		g1.init();
		g1.disPlay();
		
		//�޸���Ϣ
		g1.setAdviser("Miracle");
		g1.setSubject("�����");
		
		g1.disPlay("Miracle","�����");
	}
}
