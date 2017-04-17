#include "ch02.h"
int y_or_n_ques(const char *question)
{
   fputs (question, stdout);     /* 输出提问 */
   while(1){
      int c, answer;
      fputc (' ', stdout);       /* 写一空格分开问题与回答 */
       /* 读此行第一个字符.它应当是回答字符，但也可能不是. */
      c = tolower(fgetc (stdin));
      answer = c;
      while(c != '\n' && c != EOF)   /* 忽略此行的其余字符. */
          c = fgetc(stdin);
       /* 如果是回答字符，响应回答. */
      if (answer == 'y')
          return 1;
      if (answer == 'n')
          return 0;
       /* 非回答字符，继续要求合法回答. */
      fputs ("Please answer y or n:", stdout);
   }
}
