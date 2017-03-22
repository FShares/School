package exm3;

/**
 * Created by Administrator on 3/8/2017.
 */
public class Date {
    private String date;//日期字符串
    /**
     * 无参构造函数
     */
    public Date(){}
    /**
     * 有参构造函数
     */
    public Date(String date){
        setDate(date);
    }
    /**
     * 设置日期
     */
    public void setDate(String date) {
        String[] arr = date.split("-");
        if (arr.length != 3) {
            System.out.println("程序输出：日期非法");
            return;
        }
        int yyyy, mm, dd;
        try {
            yyyy = Integer.parseInt(arr[0]);
            mm = Integer.parseInt(arr[1]);
            dd = Integer.parseInt(arr[2]);
        } catch (Exception e) {
            System.out.println("程序输出：日期非法");
            return;
        }
        //如果年或月或日的范围不正确,则示错并返回
        if ((yyyy < 1900 || yyyy > 2050) || (mm < 1 || mm > 12) || (dd < 1 || dd > getMaxDate(yyyy, mm))) {
            System.out.println("程序输出：日期非法");
            return;
        }
        this.date = date;
    }
    /**
     * 取得日期
     */
    public String getDate() {
        return date;
    }
    /**
     * 取得当前日期的后一天
     */
    public String getNextDate() {
        String[] arr = date.split("-");
        int yyyy, mm, dd;
        yyyy = Integer.parseInt(arr[0]);                //year
        mm = Integer.parseInt(arr[1]);                  //month
        dd = Integer.parseInt(arr[2]);                  //day
        if (dd < getMaxDate(yyyy,mm)) {
            return yyyy + "-" + mm + "-" + (dd + 1);
        }
        if (mm == 12) {
            return (yyyy + 1) + "-1-1";
        }
        return yyyy + "-" + (mm + 1) + "-1";
    }
    /**
     * 判断是否是闰年
     */
    public boolean isLeapYear(int yyyy){
        if( (yyyy%4==0 && yyyy%100!=0) || yyyy%400==0 ){
            return true;
        }
        return false;
    }
    /**
     * 根据年份和月份, 返回该年该月的最大日期数
     */
    public int getMaxDate(int yyyy,int mm){
        int maxDate;
        switch (mm) {
            case 2:
                maxDate=28;
                if(isLeapYear(yyyy)){
                    maxDate=29;
                }
                break;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                maxDate=31;
                break;
            default:
                maxDate=30;
                break;
        }
        return maxDate;
    }
}