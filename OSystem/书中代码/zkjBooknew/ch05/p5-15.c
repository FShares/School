#include "ch05.h"
#define SCORES_FILE "/tmp/score"
static uid_t euid, ruid;  /* 保存有效和实际UIDS*/
void do_setuid(void)      /* 恢复原来的有效UID */
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

void undo_setuid(void) /* 设置有效UID为实际UID */
{   int status;
#ifdef _POSIX_SAVED_IDS
   status = setuid(ruid);
#else
   status = setreuid(euid, ruid);
#endif
   if (status < 0) 
      err_exit("Couldn't set uid");
}

int record_score(int score) /* 记录得分 */
{
   FILE *stream;
   char *myname;
   do_setuid ();     /* 让游戏者有读写得分文件的权利 */
   stream = fopen (SCORES_FILE, "a");   /* 打开得分文件 */
   undo_setuid();    /* 收回游戏者读写得分文件的权利,不影响后面的写操作 */
   /* 写得分至记分文件 */
   if (stream) {
      myname = cuserid((char *)NULL);  /* 游戏运行者的用户名 */
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
   /* 保存实际和有效用户IDs */
   ruid = getuid();
   euid = geteuid();
   undo_setuid();             /* 让游戏者只有他自己的权利 */
   /* 进行游戏并记录得分 */
   /* ... */
}
