package exm5;

public class Rectangle {
	protected double width;
	protected double height;
	
	protected double getArea(double w, double h){
		//��������
		return w*h;
	}
	protected double getLength(double w, double h){
		//������ܳ�
		return 2*(w+h);
	}
}
