#include "ch12.h"
#include "p12-7.c"    // make_socket()
int listenfd, connfd;
void sig_urg(int signo);
//#include "newp12-17.c" 

int main(int argc,char **argv) /* 运行命令为： <程序名> <端口号> */
{
   int n;
   char buff[40];
   sigset_t mask, oldmask;
   struct sigaction action;

   if(argc != 2) {   /* 检查参数*/
      printf("Usage: a.out <port#>\n");
      exit(1);
   }
   /* 设置sigaction结构指明信号动作. */
   action.sa_handler = sig_urg;
   sigemptyset(&action.sa_mask);
   action.sa_flags = SA_RESTART;
   sigemptyset(&mask);
   sigaddset(&mask, SIGURG);
   action.sa_mask = mask;
   /* 设置SIGURG的句柄 */
   sigaction(SIGURG, &action , NULL);
   /* 暂时阻塞SIGURG中断. */
   sigemptyset(&mask);
   sigaddset(&mask, SIGURG);
   sigprocmask (SIG_BLOCK, &mask, NULL);
   listenfd = make_socket(SOCK_STREAM, atoi(argv[1])); /* 建立侦听套接字 */
   listen(listenfd, 5);
   connfd = accept(listenfd, NULL, NULL); /* 接收连接 */
   /*  下面这一行与程序12-17 给出的信号句柄配合使用 */
   /* setsockopt(listenfd,SOL_SOCKET,SO_OOBINLINE,&n,(socklen_t)sizeof(n)); */
   fcntl(connfd,F_SETOWN,getpid());
   /* 放开对SIGURG的阻塞 */ 
   sigprocmask (SIG_UNBLOCK, &mask, NULL);
   sleep(1);    // 让程序p12-14运行
   while(1){
      if ((n = read(connfd, buff, 18 /*sizeof(buff)-1i*/)) == 0){
         printf("received EOF\n");
         exit(0);
      } else if(n>0) {
         buff[n] = 0;
         printf("read %d bytes:   %s\n",n, buff);
      } else if(errno == EINTR)
         continue;
      else
         err_exit("read error");
   }
}
void sig_urg(int signo)/* SIGURG信号处理句柄，用程序12-17时屏蔽此句柄 */  
{
   int n;
   char oob_buf[8];
   fprintf(stderr, "SIGURG received: ");
   n = recv(connfd,oob_buf,sizeof(oob_buf),MSG_OOB);
   if(n<0) 
      err_exit("read OOB error");
   oob_buf[n] = 0;
   fprintf(stderr, "read %d OOB byte: %s\n",n,oob_buf);
}

