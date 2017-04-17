#include "ch10.h"

void input_ready(int signo);
FILE *file;

int main(void)
{
   int flags;
   char buffer[64];
   struct termios newsettings,oldsettings;

   file=fopen("tstfile", "w");   // 打开输出文件
   signal(SIGIO, input_ready);   // 安装SIGIO信号句柄
 // 设置标准输入为每次读入一字符的非加工方式
   tcgetattr(STDIN_FILENO, &oldsettings);
   newsettings = oldsettings;
   newsettings.c_lflag &= (~ICANON);
   newsettings.c_cc[VTIME] = 0;
   newsettings.c_cc[VMIN] = 1;
   tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);
 // 设置标准输入为无阻塞SIGIO信号驱动IO方式
   fcntl(STDIN_FILENO, F_SETOWN, getpid());
   flags = fcntl(STDIN_FILENO, F_GETFL, 0);
   flags = flags | O_ASYNC;//|O_NONBLOCK;
   fcntl(STDIN_FILENO, F_SETFL, flags);
   while (1) sleep(1);  // 没有输入时休息
}

void input_ready(int signo) // 接收输入，积累至一行后输出。行首字符为q终止进程
{
   char c,input[80];
   int n;
   static int i=0;

   if (read(STDIN_FILENO, &c, 1)>0) {
      if (c != '\n')
         input[i++]=c;
      else {
        input[i++]='\0';
        fprintf(file, "received %d SIGIOs, and Input line is: %s\n", i, input);
        i=0;
        if (input[0]=='q') {
           fclose(file);
           _exit(0);
        }
      }
   }
}
