#include "ch04.h"

char *get_perms(struct stat *sbuf, char *perms)
{
   static char *modes[] = {   /* 与每一种访问权限许可值对应的字符串 */
       "---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"
   };  
   int i,j;

   *perms = '\0';
   /* 分别获得三组访问权限值，用该值作为数组modes的下标，以便获得对应的字符串拼入perms */
   for (i=2; i>=0; i--) {
      j=(sbuf->st_mode>>(i*3)) & 07;
      strcat( perms,modes[j]);
   }
   /*  处理调整ID位和sticky位 */
   if ((sbuf->st_mode & S_ISUID) !=0)
      perms[2] = 's';
   if ((sbuf->st_mode & S_ISGID) !=0)
      perms[5] = 's';
   if ((sbuf->st_mode & S_ISUID) !=0)
      perms[8] = 't';
   return perms;
}
