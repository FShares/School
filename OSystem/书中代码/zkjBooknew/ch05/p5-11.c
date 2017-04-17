#include <pwd.h>
#include <string.h>
struct passwd *getpwnam (const char *name)
{
   struct passwd *ptr;
   setpwent();                                  /* 打开用户数据库 */
   while((ptr = getpwent()) != NULL) {
      if (strcmp(name, ptr->pw_name) == 0)
         break;                                  /* 找到匹配项 */
   }
   endpwent();                                  /* 关闭用户数据库 */
   return(ptr);                                 /* 找不到匹配时ptr为NULL */
}
