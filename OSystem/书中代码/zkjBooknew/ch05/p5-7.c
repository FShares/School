#include "ch05.h"
typedef enum{
  ST_PROGRAM, ST_FUNCTION, ST_SUBROUTINE, ST_END, ST_NONE // 其它语句类型...
} statement;
jmp_buf eof_buf;
int parse_file(void)
{
   statement st;
   if (setjmp(eof_buf)){  /* 设置出错返回点 */
      error("Unexpected end of file in '%s'", source_file);
      return FAILUR;	 /* 遇到非正常的EOF  */
   }
   while((st = next_statement())!= ST_NONE)  /* 正常的EOF，结束扫描  */
      switch (st) {
      case ST_PROGRAM:     /* 段首语句  */
      case ST_SUBROUTINE:
      case ST_FUNCTION:
          accept_statement(st);
          parse_progunit(); 
          break;
          /* 其它段首语句处理  */
      }
   /* 后继处理 ...  */  
   return SUCCESS;
}
void parse_progunit()
{ 
   statement st;
   st = parse_spec();        /* 扫描说明语句  */
   if (st == ST_NONE)
	  longjmp(eof_buf, 1);  /* 遇到非正常的EOF，直接返回到主控过程  */
   else if (st == ST_END) {   /* 段尾语句  */
      accept_statement(st);
      goto done;
   }
   parse_executable(st);     /* 扫描执行语句  */
done: ; /* 后继处理  */
}
parse_executable(statement st)  /* 扫描执行语句，包括段尾语句  */
{
   for (;; st = next_statement())
      switch (st) {
	  case ST_NONE:  
	     longjmp (eof_buf, 1); /* 遇到非正常的EOF，直接返回到主控过程  */
	  case ST_END:      /* 段尾语句  */
	     accept_statement(st);
	     return;
	  case ST_IF_BLOCK:
	     parse_if_block();
	     continue;
	  case ST_DO:
	     parse_do_block();
	     continue;
	  /* 其它可执行语句处理...  */
	 }
}
