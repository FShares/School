package exm3;
import java.util.Scanner;

public class ex33 {
    public static void main(String[] args) {
        Scanner input=new Scanner(System.in);
        System.out.println("请按'yyyy-mm-dd'格式输入一个日期(输入'no'则退出),程序将输出下一天的日期:");
        do{
            System.out.print("用户输入:");
            String strDate=input.next();
            if(strDate.equals("no")){
                System.out.println("程序退出!");
                break;
            }
            Date date=new Date(strDate);
            if(date.getDate()!=null){
                System.out.println("程序输出:"+date.getNextDate());
            }
            System.out.println();
        }while(true);
    }
}