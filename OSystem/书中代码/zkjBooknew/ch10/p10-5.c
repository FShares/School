#include "ch10.h"

void input_ready(int signo);
FILE *file;

int main(void)
{
   int flags;
   char buffer[64];
   struct termios newsettings,oldsettings;

   file=fopen("tstfile", "w");   // ������ļ�
   signal(SIGIO, input_ready);   // ��װSIGIO�źž��
 // ���ñ�׼����Ϊÿ�ζ���һ�ַ��ķǼӹ���ʽ
   tcgetattr(STDIN_FILENO, &oldsettings);
   newsettings = oldsettings;
   newsettings.c_lflag &= (~ICANON);
   newsettings.c_cc[VTIME] = 0;
   newsettings.c_cc[VMIN] = 1;
   tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);
 // ���ñ�׼����Ϊ������SIGIO�ź�����IO��ʽ
   fcntl(STDIN_FILENO, F_SETOWN, getpid());
   flags = fcntl(STDIN_FILENO, F_GETFL, 0);
   flags = flags | O_ASYNC;//|O_NONBLOCK;
   fcntl(STDIN_FILENO, F_SETFL, flags);
   while (1) sleep(1);  // û������ʱ��Ϣ
}

void input_ready(int signo) // �������룬������һ�к�����������ַ�Ϊq��ֹ����
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
