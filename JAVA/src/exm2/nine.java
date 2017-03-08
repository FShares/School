package exm2;
public class nine {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        System.out.println("==========我的小九九======");
        int x,y;

        for(x = 0;x <= 9; x++)
        {
            for(y = 1;y <= x; y++)
            {
                System.out.print(y+"*"+x+"="+x*y+"\t");
            }
            System.out.println();
        }
    }

}
