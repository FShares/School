#include <stdio.h>
#include <string.h>
main()
{
  char a[30] = "string(1)";
  char b[] = "string(2)";
  printf("before strcpy() : %s\n",a);
  printf("after strcpy(): %s\n", strcpy(a,b));
}
