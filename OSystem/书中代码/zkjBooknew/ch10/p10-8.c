#include "ch10.h"
#define NBUFFERS 2            /* 缓冲区个数 */
#define BUFFERSIZE 2048       /* 缓冲区大小 */
#define BLOCKSIZE  1024       /* 每次读入的数据块大小 */
#define SIG_AIO_WRITE (SIGRTMIN+5)

typedef enum {BUFFER_FREE=1,BUFFER_FILLING,BUFFER_WRITING} BUFFLAG;
typedef struct {
   BUFFLAG state;              /* 缓冲区状态 */
   int fillpt;                 /* 缓冲区中最后一个数据位置 */
   struct aiocb acb;           /* 异步输出控制块 */
   char buffer [BUFFERSIZE];   /* 数据缓冲区 */
} buffer_t;
static buffer_t buf_list[NBUFFERS];
static sigset_t aio_completion_signal;
static volatile int sigcnt = 0, total = 0;
static off_t seek_ptr;

/* 异步输出完成信号句柄 */
void aio_ok(int signo, siginfo_t *info, void *ignored)
{
   buffer_t *donebuf;
   ssize_t rval;
   if ((signo != SIG_AIO_WRITE)||info->si_code!=SI_ASYNCIO)
      return; // 非AIO完成信号   
   else
      printf("AIO write completed\n");
/* 根据info获得异步I/O相关的信息。 */
   donebuf = (buffer_t *)info->si_value.sival_ptr;
   if ((aio_error((struct aiocb *) &donebuf->acb) != EINPROGRESS))
      rval=aio_return((struct aiocb *) &donebuf->acb);
/* 累计写出的字节数和信号发生次数，并标记缓冲区已空*/
   total += rval; sigcnt++;
   donebuf->state = BUFFER_FREE;
   donebuf->fillpt = 0;
   return;
}
buffer_t *find_free_buf (void) /* 获得一个空闲的缓冲区 */
{
   int i;
   sigset_t prevmask;
   sigprocmask(SIG_BLOCK, &aio_completion_signal, &prevmask);
   while (1) {
      for (i=0; i<NBUFFERS; i++) {
         if (buf_list[i].state == BUFFER_FREE)
            break;
      }
      if (i == NBUFFERS) 
         sigsuspend(&prevmask);  /* 没有空闲缓冲区，等待某个异步输出完成后再试。*/
      else
         break;
   }
   buf_list[i].state = BUFFER_FILLING; /* 找到了空闲缓冲区，标志它正被使用 */
   buf_list[i].fillpt = 0;
   sigprocmask(SIG_SETMASK, &prevmask, NULL);
   return (&buf_list[i]);
}
void flush_filled_buf(buffer_t *full_guy) /* 写出缓冲区中的数据 */
{
   /* 设置 AIOCB */
   full_guy->acb.aio_offset = seek_ptr;
   seek_ptr += full_guy->fillpt;
   full_guy->acb.aio_buf = full_guy->buffer;
   full_guy->acb.aio_nbytes = full_guy->fillpt;
   full_guy->acb.aio_reqprio = 0;
   full_guy->acb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   full_guy->acb.aio_sigevent.sigev_signo = SIG_AIO_WRITE;
   full_guy->acb. aio_sigevent.sigev_value.sival_ptr = (void *)full_guy;
   full_guy->state = BUFFER_WRITING; /* 标志缓冲区状态为正在写出*/  
   if (aio_write(&full_guy->acb) < 0) /* 发出异步输出请求 */
      perror ( "aio_write" ) ;
   return;
}
main(int argc, char **argv)
{
   int  i, in_file, out_file;
   buffer_t *currentbuf;
   struct sigaction sig_act;
   int chunksize;
   if (argc != 4) {/* 检查参数个数 */
      fprintf(stderr, "Usage: %s input-file output-file buf-size-in-Kb\n",
               argv[0]);
      exit(0);
   }
   /* 打开输入和输出文件 */
   if ((in_file = open(argv[1], O_RDONLY)) == -1) 
      err_exit(argv[1]);
   if ((out_file = open(argv[2], O_WRONLY|O_CREAT, 0777)) == -1)
      err_exit(argv[2]);
   chunksize=atol(argv[3])*BLOCKSIZE;
    /* 初始缓冲区状态并分配一个复制文件的缓冲区 */
   for (i=0; i<NBUFFERS; i++){
      buf_list[i].acb.aio_fildes = out_file;
      buf_list[i].state = BUFFER_FREE;
      buf_list[i].fillpt = 0;
   }
   currentbuf = find_free_buf();
	   /* 建立异步I/O完成信号句柄 */
   sigemptyset(&aio_completion_signal);
   sigaddset(&aio_completion_signal, SIG_AIO_WRITE);
   sigemptyset(&sig_act.sa_mask);                  
   sig_act.sa_flags = SA_SIGINFO;
   sig_act.sa_sigaction = aio_ok;
   if (sigaction (SIG_AIO_WRITE, &sig_act, 0) < 0)
      perror("sigaction");
	   /* 从in_file复制文件到out_file */
   while (1) {
      int nbytes;
again:
      /* 读一块信息至缓冲区 */
      nbytes = read(in_file, currentbuf->buffer+currentbuf->fillpt, 
                      chunksize);
      if (nbytes>0) {
         currentbuf->fillpt += nbytes;
         if (currentbuf->fillpt == BUFFERSIZE) {
            /* 写出已满的缓冲区并获得一个新缓冲区 */
            flush_filled_buf (currentbuf);
            currentbuf = find_free_buf() ;
         }
      } else if (nbytes == 0) { /* 到达文件尾 */
         flush_filled_buf (currentbuf);
         break;
      } else {                  
         if (errno == EINTR) goto again;  /* 被信号中断，重新读 */
         else err_exit("read");
      }
   }
   for (i=0; i<NBUFFERS; i++){  /* 等待所有异步输出完成 */
      if (buf_list[i].state == BUFFER_WRITING){
         struct aiocb *acbp[1];
         acbp[0] = &buf_list[i].acb;
         aio_suspend(acbp, 1, NULL);
      }
   }
   close(in_file);
   close(out_file);
   printf("Copied: %d bytes, %d signals taken\n", total, sigcnt);
}
