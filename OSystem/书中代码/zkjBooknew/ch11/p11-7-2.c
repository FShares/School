#include "p11-7.h"

int main()
{
   int msgid, running = 1;
   struct my_msg msgbuf;
   struct msqid_ds buf;
   /* 获得消息队列id */
   msgid = msgget((key_t)1234, 0666|IPC_CREAT);
   if (msgid == -1) 
       err_exit("msgget failed\n");
 
   /* 反复将用户输入的数据发送至消息队列，字符串“end”标志输入结束 */
   while(running) {
       /* 读输入字符串至消息缓冲区 */
       printf("Enter some text: ");         
       fgets(msgbuf.text, BUFSIZE, stdin);
       msgbuf.my_msg_type = (long int)msgbuf.text[0]; /* 第一个字符作为消息类型 */
       /* 向消息队列发送消息，阻塞方式 */
       if (msgsnd(msgid, (void *)&msgbuf, sizeof(struct my_msg), IPC_NOWAIT) == -1) 
          err_exit("msgsnd failed\n");
       /* 如果是“end”，结束循环 */
       if (strncmp(msgbuf.text, "end", 3) == 0) 
          running = 0;
   }
   exit(EXIT_SUCCESS);
}
