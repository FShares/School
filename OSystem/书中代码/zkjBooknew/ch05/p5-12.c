#include "ch05.h"

int main(void)
{
   char *me, **members;
   struct passwd  *my_passwd;
   struct group   *my_group;

   me = getlogin();             // 获获得用户ID （§6.11）
   my_passwd = getpwnam(me);    // 获得用户信息 */
   if (!my_passwd) 
      err_exit("getpwuid failed");
   
   /* 打印用户信息 */
   printf("I am %s\n", my_passwd->pw_gecos);
   printf("My login name is %s\n", my_passwd->pw_name);
   printf("My uid is %d\n", (int) (my_passwd->pw_uid));
   printf("My home directory is %s\n", my_passwd->pw_dir);
   printf("My default shell is %s\n", my_passwd->pw_shell);

   /* 获得缺省组ID信息 */
   my_group = getgrgid(my_passwd->pw_gid);
   if (!my_group) 
      err_exit("getgrgid failed");

   /* 打印组信息 */
   printf("My default group is %s (%d).\n",
           my_group->gr_name, (int) (my_passwd->pw_gid));
   members = my_group->gr_mem;
   if (*members)
     printf("The members of this group are:\n");
   else 
      printf("no other members in the group\n");
   while(*members){
      printf("  %s\n", *(members));
      members++;
   }
   return EXIT_SUCCESS;
}
