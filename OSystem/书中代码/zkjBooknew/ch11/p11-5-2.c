#include "p11-6-7.h"
int main()
{
   int server_fifo_fd, client_fifo_fd;
   struct data_to_pass my_request;
   char client_fifo_name[256];
   pid_t mypid;
   /* 打开服务管道 */   
   server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
   if (server_fifo_fd == -1) 
       err_exit("Sorry, no server");
   /* 创建以进程ID命名的客户接收有名管道 */
   mypid = getpid();
   sprintf(client_fifo_name, CLIENT_FIFO_NAME, mypid);
   if (mkfifo(client_fifo_name, 0777) == -1)
       err_exit(client_fifo_name);
   /* 向服务进程连续发送和接收数据 */
   while (1) {
       /* 形成给服务进程的数据 */
       printf ("Enter your request:");
       fgets (my_request.data, BUFFER_SIZE, stdin);
       if (strcmp(my_request.data,"bye\n")==0
                      ||strcmp(my_request.data, "BYE\n")==0)
           break;
       my_request.client_pid = mypid;
       /* 向服务进程发出请求 */
       write(server_fifo_fd, &my_request, sizeof(my_request));
       /* 从服务进程接收回答，为此，先打开客户接收有名管道 */
       client_fifo_fd = open (client_fifo_name, O_RDONLY);
       if (client_fifo_fd != -1) {
           if (read (client_fifo_fd, &my_request, sizeof(my_request)) > 0) {
               printf ("---I get answer: %s\n", my_request.data);
           }
           close(client_fifo_fd); 
       }
    }
     /* 关闭服务FIFO并删除客户接收FIFO */   
    close(server_fifo_fd);
    unlink(CLIENT_FIFO_NAME);
    exit(EXIT_SUCCESS);
}
