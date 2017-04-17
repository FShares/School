#include "ch09.h"
#define TTY_OUTPUT 1
static struct termios old_term, new_term;
void do_exit(int);
void set_tty()
{
   /* ������س��ͻ��з�������BREAK���� */
   new_term.c_iflag &= ~(ICRNL|IGNCR|INLCR|IGNBRK|BRKINT);
   new_term.c_oflag &= ~OPOST;           /* ��ʵ�ֶ����������� */
   new_term.c_lflag |= ISIG | NOFLSH;    /* �����ն��źţ��������������� */
   new_term.c_lflag &= ~(ICANON);        /* �Ǽӹ���ʽ */
   new_term.c_cc[VINTR] = 7;              /* Ctrl-g ��Ϊ�ж��ַ� */
   new_term.c_cc[VQUIT] = 8;              /* Ctrl-h ��Ϊ�˳��ַ� */
   new_term.c_cc[VMIN]  = 1;
   new_term.c_cc[VTIME] = 0;
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &new_term);
}
void tty_init()
{
   tcgetattr(TTY_OUTPUT, &old_term);
   new_term = old_term;         /* �����ն˳�ʼ״̬ */
   signal(SIGTERM, do_exit);
   signal(SIGQUIT, do_exit);
   signal(SIGINT,  do_exit);
   set_tty();
}
void tty_end()
{
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);
}
void do_exit(int signum)
{
   tty_end();
   exit(1);
}
int main()
{
   char c;
   printf("Display key sequence utility\n");
   printf("Press space when done.\n\n");
   tty_init();
   for (;;) {
      read(0, &c, 1);
      if (c == ' ')
          break;
      printf("%o\n", c);
      fflush(stdout);
   }
   tty_end();
   return 0;
}

/* ���Ʋ��� */
/*
void restore_tty()
{
   signal(SIGTSTP, SIG_DFL);                     /* ȱʡ�źž������ֹ���� */
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);  /* �ָ��ն�Ϊԭ��ʽ */
   raise (SIGTSTP);                              /* �ٴ����ɸ��źŸ�shell */
}
void tty_end()
{
   signal(SIGTSTP, restore_tty); 
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);
}
void tty_init()
{
   tcgetattr(TTY_OUTPUT, &old_term);
   signal(SIGTERM, do_exit);
   signal(SIGQUIT, do_exit);
   signal(SIGINT,  do_exit);
   signal(SIGTSTP, restore_tty); 
   signal(SIGCONT, set_tty);
   new_term = old_term;
   set_tty();
}
*/
