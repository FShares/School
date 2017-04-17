#include "ch09.h"
struct termios saved_attributes;        /* 用该变量保存原来的终端属性 */
void resume_input_mode(void)
{
   tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}
void set_input_mode(int fd)
{
   struct termios tattr;
   char *name;
   if (!isatty(fd)) { /* 保证fd 是终端 */
      fprintf(stderr, "Not a terminal.\n"); exit (EXIT_FAILURE);
   }
   tcgetattr(fd, &saved_attributes); /* 保存当前终端属性*/
	   /* 设置终端为非加工、不回显方式 */
   tcgetattr(fd, &tattr);
   tattr.c_lflag &= ~(ICANON|ECHO); /* 清除 ICANON和ECHO */
   tattr.c_cc[VMIN] = 1;  /* 等待至少读一个字符 */
   tattr.c_cc[VTIME] = 0;
   tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}
int main (void)
{
   char c;
   set_input_mode(STDIN_FILENO);
   while (1){
       read (STDIN_FILENO, &c, 1);
       if (c == '\004')          /* Ctrl-d */
          break;
       else
          printf("I read %c\n",c);
    }
    resume_input_mode(); /* 恢复终端属性 */
    return EXIT_SUCCESS;
 }
