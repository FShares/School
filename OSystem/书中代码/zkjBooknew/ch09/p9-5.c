#include "ch09.h"
#define TTY_OUTPUT 1
static struct termios old_term, new_term;
void do_exit(int);
void set_tty()
{
   /* 不处理回车和换行符，忽略BREAK条件 */
   new_term.c_iflag &= ~(ICRNL|IGNCR|INLCR|IGNBRK|BRKINT);
   new_term.c_oflag &= ~OPOST;           /* 无实现定义的输出处理 */
   new_term.c_lflag |= ISIG | NOFLSH;    /* 生成终端信号，但不清除输出队列 */
   new_term.c_lflag &= ~(ICANON);        /* 非加工方式 */
   new_term.c_cc[VINTR] = 7;              /* Ctrl-g 作为中断字符 */
   new_term.c_cc[VQUIT] = 8;              /* Ctrl-h 作为退出字符 */
   new_term.c_cc[VMIN]  = 1;
   new_term.c_cc[VTIME] = 0;
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &new_term);
}
void tty_init()
{
   tcgetattr(TTY_OUTPUT, &old_term);
   new_term = old_term;         /* 保存终端初始状态 */
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

/* 改善部分 */
/*
void restore_tty()
{
   signal(SIGTSTP, SIG_DFL);                     /* 缺省信号句柄，中止程序 */
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);  /* 恢复终端为原方式 */
   raise (SIGTSTP);                              /* 再次生成该信号给shell */
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
