#include "ch06.h"
int main(void)
{
   char *myargv[]={"ls", "-l", "..", (char *)0};
   //execv("/bin/ls",myargv);
   execvp("ls",myargv);
}
