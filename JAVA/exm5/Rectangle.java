package exm5;

public class Rectangle {
	protected double width;
	protected double height;
	
	protected double getArea(double w, double h){
		//求矩形面积
		return w*h;
	}
	protected double getLength(double w, double h){
		//求矩形周长
		return 2*(w+h);
	}
}
