package exm5;
/*
 * ���һ��User�࣬���а����û���������������Լ����췽������������2 ������
 * ��ȡ�����ÿ���ķ�������ʾ���޸��û����ķ����ȡ���дӦ�ó������User�ࡣ  
 */
public class ex3 {

	public static void main(String[] args) {
		
		User u1 = new User();
		
		 //���췽���еĳ�ʼ�û���������
		System.out.println("u1 name: "+u1.getUserName());
		System.out.println("u1 name: "+u1.getUserPass());
		
		//ͨ��User���еķ�����ֵ
		u1.setUserName("Administrator");
		u1.setUserPass("Dj#dsEjf832");
		
		//���

		System.out.println("u1 name: "+u1.getUserName());
		System.out.println("u1 name: "+u1.getUserPass());
	}

}
