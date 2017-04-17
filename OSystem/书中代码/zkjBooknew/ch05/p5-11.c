#include <pwd.h>
#include <string.h>
struct passwd *getpwnam (const char *name)
{
   struct passwd *ptr;
   setpwent();                                  /* ���û����ݿ� */
   while((ptr = getpwent()) != NULL) {
      if (strcmp(name, ptr->pw_name) == 0)
         break;                                  /* �ҵ�ƥ���� */
   }
   endpwent();                                  /* �ر��û����ݿ� */
   return(ptr);                                 /* �Ҳ���ƥ��ʱptrΪNULL */
}
