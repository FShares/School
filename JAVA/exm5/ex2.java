package exm5;

import java.util.Scanner;

/*
 *��1������Rectangle�࣬�������width��height��  
 *��2����Rectangle����������ַ���������ε��ܳ�������� 
 *��3���������Rectangle���һ�����ε��ܳ������
 */
public class ex2 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		System.out.println("�������͸ߣ�");
		Scanner sc=new Scanner(System.in);
		double width = sc.nextDouble();
		double height = sc.nextDouble();
		
		//���� re ����
		Rectangle re = new Rectangle();
		//���� re �е� ���ܳ����������
		double area = re.getArea(width, height);
		double length = re.getLength(width, height);
		
		//������
		System.out.println("�����"+area);
		System.out.println("�ܳ���"+length);
	}

}
