#include "ch09.h"
/*命令菜单*/
char *menu[]={"a-add new record", "d-delete record", "q-quit", NULL}; 
int getchoice(char *greet, char *choices[])
{
   int selected, chosen = 0;
   char **option;
   do{
      printf( "Choice: %s\n", greet);
      option = choices;
	  while(*option) {     /* 打印菜单 */
          printf ("%s\n", *option);
          option++;
      }
      selected = getchar();  /* 读入命令字符 */
      option = choices;
      while(*option){         /* 检查命令字符，正确则置chosen=1*/
         if(selected == *option[0]) {
            chosen = 1;
            break;
         }
         option++;
	  }
      if(!chosen)   /* 若命令不正确，提示重新输入命令，直至得到正确的命令*/
      printf("Incorrect choice,please select agian\n");
   } while(!chosen); 
   return selected;
}
int main(void)
{
   int choice = 0;
   do {
      choice = getchoice("Please select a action", menu);
      printf ("Your choice is: %c\n", choice);
   } while (choice != 'q') ;
   exit (0);
}
