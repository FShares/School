
public class nine {
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        System.out.print("==========================我的小九九======================");
        int x,y;
        for(x = 0;x <= 9; x++)
        {
            for(y = 1;y <= x; y++)
            {
                //输出九乘九表
                System.out.print(y+"*"+x+"="+x*y+"\t");
            }
            System.out.println();
        }
    }

}
