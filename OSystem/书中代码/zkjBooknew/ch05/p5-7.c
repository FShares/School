#include "ch05.h"
typedef enum{
  ST_PROGRAM, ST_FUNCTION, ST_SUBROUTINE, ST_END, ST_NONE // �����������...
} statement;
jmp_buf eof_buf;
int parse_file(void)
{
   statement st;
   if (setjmp(eof_buf)){  /* ���ó����ص� */
      error("Unexpected end of file in '%s'", source_file);
      return FAILUR;	 /* ������������EOF  */
   }
   while((st = next_statement())!= ST_NONE)  /* ������EOF������ɨ��  */
      switch (st) {
      case ST_PROGRAM:     /* �������  */
      case ST_SUBROUTINE:
      case ST_FUNCTION:
          accept_statement(st);
          parse_progunit(); 
          break;
          /* ����������䴦��  */
      }
   /* ��̴��� ...  */  
   return SUCCESS;
}
void parse_progunit()
{ 
   statement st;
   st = parse_spec();        /* ɨ��˵�����  */
   if (st == ST_NONE)
	  longjmp(eof_buf, 1);  /* ������������EOF��ֱ�ӷ��ص����ع���  */
   else if (st == ST_END) {   /* ��β���  */
      accept_statement(st);
      goto done;
   }
   parse_executable(st);     /* ɨ��ִ�����  */
done: ; /* ��̴���  */
}
parse_executable(statement st)  /* ɨ��ִ����䣬������β���  */
{
   for (;; st = next_statement())
      switch (st) {
	  case ST_NONE:  
	     longjmp (eof_buf, 1); /* ������������EOF��ֱ�ӷ��ص����ع���  */
	  case ST_END:      /* ��β���  */
	     accept_statement(st);
	     return;
	  case ST_IF_BLOCK:
	     parse_if_block();
	     continue;
	  case ST_DO:
	     parse_do_block();
	     continue;
	  /* ������ִ����䴦��...  */
	 }
}
