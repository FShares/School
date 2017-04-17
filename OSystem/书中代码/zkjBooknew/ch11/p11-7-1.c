#include "p11-7.h"
int main(void)
{
   int running = 1, msgid;    
   struct my_msg msgbuf;
   long int msg_type = -57;    /* ���Ƚ�������С��57����Ϣ */
   /* ����/����Ϣ���� */
   if ((msgid = msgget((key_t)1234, 0666|IPC_CREAT)) == -1) 
      err_exit("msgget failed");
   /* �Ӷ����з���������Ϣ��ֱ���յ��ַ�����end�� */
   while(running) {/* ���Ƚ�������С��57����Ϣ,���ȴ� */
      if (msgrcv(msgid, (void *)&msgbuf, BUFSIZ, -57, IPC_NOWAIT)!= -1)
         printf("You wrote: %s", msgbuf.text);        /* ��ʾ�յ�����Ϣ */
      else if (errno==ENOMSG /* ������˳�������Ϣ */
                && msgrcv(msgid, (void *)&msgbuf, BUFSIZ, 0, 0) != -1)
         printf("You wrote: %s", msgbuf.text);        /* ��ʾ�յ�����Ϣ */
      else 
         err_exit ("msgrcv failed\n");
      if (strncmp(msgbuf.text, "end", 3) == 0)
         break;
   }
   /* ɾ����Ϣ���� */
   if (msgctl(msgid, IPC_RMID, 0) == -1) 
      err_exit("msgctl(IPC_RMID) failed\n");
   exit(EXIT_SUCCESS);
}
