#include "ch05.h"
#define SCORES_FILE "/tmp/score"
static uid_t euid, ruid;  /* ������Ч��ʵ��UIDS*/
void do_setuid(void)      /* �ָ�ԭ������ЧUID */
{
   int status;
#ifdef _POSIX_SAVED_IDS
   status = setuid(euid);
#else
   status = setreuid(ruid, euid);
#endif
   if (status < 0) 
      err_exit("Couldn't set uid");
}

void undo_setuid(void) /* ������ЧUIDΪʵ��UID */
{   int status;
#ifdef _POSIX_SAVED_IDS
   status = setuid(ruid);
#else
   status = setreuid(euid, ruid);
#endif
   if (status < 0) 
      err_exit("Couldn't set uid");
}

int record_score(int score) /* ��¼�÷� */
{
   FILE *stream;
   char *myname;
   do_setuid ();     /* ����Ϸ���ж�д�÷��ļ���Ȩ�� */
   stream = fopen (SCORES_FILE, "a");   /* �򿪵÷��ļ� */
   undo_setuid();    /* �ջ���Ϸ�߶�д�÷��ļ���Ȩ��,��Ӱ������д���� */
   /* д�÷����Ƿ��ļ� */
   if (stream) {
      myname = cuserid((char *)NULL);  /* ��Ϸ�����ߵ��û��� */
      if (score < 0)
         fprintf (stream, "%10s: Couldn't lift the caber.\n",myname);
      else
         fprintf (stream, "%10s: %d feet.\n", myname, score);
      fclose (stream);
      return 0;
   }
   else
      return -1;
}
int main(void)
{
   /* ����ʵ�ʺ���Ч�û�IDs */
   ruid = getuid();
   euid = geteuid();
   undo_setuid();             /* ����Ϸ��ֻ�����Լ���Ȩ�� */
   /* ������Ϸ����¼�÷� */
   /* ... */
}
