#include "p11-7.h"
int main(void)
{
   int running = 1, msgid;    
   struct my_msg msgbuf;
   long int msg_type = -57;    /* 优先接收类型小于57的消息 */
   /* 创建/打开消息队列 */
   if ((msgid = msgget((key_t)1234, 0666|IPC_CREAT)) == -1) 
      err_exit("msgget failed");
   /* 从队列中反复接收消息，直至收到字符串”end” */
   while(running) {/* 优先接收类型小于57的消息,不等待 */
      if (msgrcv(msgid, (void *)&msgbuf, BUFSIZ, -57, IPC_NOWAIT)!= -1)
         printf("You wrote: %s", msgbuf.text);        /* 显示收到的消息 */
      else if (errno==ENOMSG /* 按正常顺序接收消息 */
                && msgrcv(msgid, (void *)&msgbuf, BUFSIZ, 0, 0) != -1)
         printf("You wrote: %s", msgbuf.text);        /* 显示收到的消息 */
      else 
         err_exit ("msgrcv failed\n");
      if (strncmp(msgbuf.text, "end", 3) == 0)
         break;
   }
   /* 删除消息队列 */
   if (msgctl(msgid, IPC_RMID, 0) == -1) 
      err_exit("msgctl(IPC_RMID) failed\n");
   exit(EXIT_SUCCESS);
}
