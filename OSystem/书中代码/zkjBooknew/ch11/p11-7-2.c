#include "p11-7.h"

int main()
{
   int msgid, running = 1;
   struct my_msg msgbuf;
   struct msqid_ds buf;
   /* �����Ϣ����id */
   msgid = msgget((key_t)1234, 0666|IPC_CREAT);
   if (msgid == -1) 
       err_exit("msgget failed\n");
 
   /* �������û���������ݷ�������Ϣ���У��ַ�����end����־������� */
   while(running) {
       /* �������ַ�������Ϣ������ */
       printf("Enter some text: ");         
       fgets(msgbuf.text, BUFSIZE, stdin);
       msgbuf.my_msg_type = (long int)msgbuf.text[0]; /* ��һ���ַ���Ϊ��Ϣ���� */
       /* ����Ϣ���з�����Ϣ��������ʽ */
       if (msgsnd(msgid, (void *)&msgbuf, sizeof(struct my_msg), IPC_NOWAIT) == -1) 
          err_exit("msgsnd failed\n");
       /* ����ǡ�end��������ѭ�� */
       if (strncmp(msgbuf.text, "end", 3) == 0) 
          running = 0;
   }
   exit(EXIT_SUCCESS);
}
