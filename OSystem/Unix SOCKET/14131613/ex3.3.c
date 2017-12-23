#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[]){
  struct in_addr addr1, addr2;
  unsigned long l1,l2;
  char *p1, *p2;
  int i;
  l1 = inet_addr("192.168.0.74");
  l2 = inet_addr("211.100.21.179");
  printf("%u\n",l1);
  for(i =0;i<4;i++)
  {
    printf("%02x",*((unsigned char*)(&l1)+i));
  }
  printf("\n");
  printf("%u\n",l2);
  for(i=0;i<4;i++)
  {
   printf(" %02x",*((unsigned char*)(&l2)+i));
  }
  printf("\n");
  memcpy(&addr1, &l1,4);
  memcpy(&addr2, &l2,4);
  printf("%s\n",inet_ntoa(addr1));
  printf("%s\n",inet_ntoa(addr2));
  p1= inet_ntoa(addr1);
  p2=inet_ntoa(addr2);
  printf("%s\n",p1);
  printf("%s\n",p2);
  return 0;


}
