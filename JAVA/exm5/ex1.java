package exm5;
/*
 * д��һ����People�����ɸ�������������������Employee��Teacher��
 * ����People �����name��age����������Ա������
 * �ֱ�ΪString���͡����ͣ��Ҿ�
 * �й��е�getAge��Ա���������ڷ���age������ֵ��
 * Employee����б�����Ա����empno,Teacher����teano��zc��Ա������
 */
public class ex1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//People p1 = new People();
		Employee e1 = new Employee();		//����e1����
		e1.name="����";
		Teacher t1 = new Teacher();
		t1.name="����";
		t1.age=23;
		System.out.println("Employee name:"+e1.name);
		System.out.println("Employee Age:"+e1.getAge());	//����e1�ĸ���getAge()����
		System.out.println("Teacher name:"+t1.name);
		System.out.println("Teacher Age:"+t1.getAge());
	}

}
