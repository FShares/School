#include "ch09.h"
/*����˵�*/
char *menu[]={"a-add new record", "d-delete record", "q-quit", NULL}; 
int getchoice(char *greet, char *choices[])
{
   int selected, chosen = 0;
   char **option;
   do{
      printf( "Choice: %s\n", greet);
      option = choices;
	  while(*option) {     /* ��ӡ�˵� */
          printf ("%s\n", *option);
          option++;
      }
      selected = getchar();  /* ���������ַ� */
      option = choices;
      while(*option){         /* ��������ַ�����ȷ����chosen=1*/
         if(selected == *option[0]) {
            chosen = 1;
            break;
         }
         option++;
	  }
      if(!chosen)   /* �������ȷ����ʾ�����������ֱ���õ���ȷ������*/
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
