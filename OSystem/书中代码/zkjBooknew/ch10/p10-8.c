#include "ch10.h"
#define NBUFFERS 2            /* ���������� */
#define BUFFERSIZE 2048       /* ��������С */
#define BLOCKSIZE  1024       /* ÿ�ζ�������ݿ��С */
#define SIG_AIO_WRITE (SIGRTMIN+5)

typedef enum {BUFFER_FREE=1,BUFFER_FILLING,BUFFER_WRITING} BUFFLAG;
typedef struct {
   BUFFLAG state;              /* ������״̬ */
   int fillpt;                 /* �����������һ������λ�� */
   struct aiocb acb;           /* �첽������ƿ� */
   char buffer [BUFFERSIZE];   /* ���ݻ����� */
} buffer_t;
static buffer_t buf_list[NBUFFERS];
static sigset_t aio_completion_signal;
static volatile int sigcnt = 0, total = 0;
static off_t seek_ptr;

/* �첽�������źž�� */
void aio_ok(int signo, siginfo_t *info, void *ignored)
{
   buffer_t *donebuf;
   ssize_t rval;
   if ((signo != SIG_AIO_WRITE)||info->si_code!=SI_ASYNCIO)
      return; // ��AIO����ź�   
   else
      printf("AIO write completed\n");
/* ����info����첽I/O��ص���Ϣ�� */
   donebuf = (buffer_t *)info->si_value.sival_ptr;
   if ((aio_error((struct aiocb *) &donebuf->acb) != EINPROGRESS))
      rval=aio_return((struct aiocb *) &donebuf->acb);
/* �ۼ�д�����ֽ������źŷ�������������ǻ������ѿ�*/
   total += rval; sigcnt++;
   donebuf->state = BUFFER_FREE;
   donebuf->fillpt = 0;
   return;
}
buffer_t *find_free_buf (void) /* ���һ�����еĻ����� */
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
         sigsuspend(&prevmask);  /* û�п��л��������ȴ�ĳ���첽�����ɺ����ԡ�*/
      else
         break;
   }
   buf_list[i].state = BUFFER_FILLING; /* �ҵ��˿��л���������־������ʹ�� */
   buf_list[i].fillpt = 0;
   sigprocmask(SIG_SETMASK, &prevmask, NULL);
   return (&buf_list[i]);
}
void flush_filled_buf(buffer_t *full_guy) /* д���������е����� */
{
   /* ���� AIOCB */
   full_guy->acb.aio_offset = seek_ptr;
   seek_ptr += full_guy->fillpt;
   full_guy->acb.aio_buf = full_guy->buffer;
   full_guy->acb.aio_nbytes = full_guy->fillpt;
   full_guy->acb.aio_reqprio = 0;
   full_guy->acb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   full_guy->acb.aio_sigevent.sigev_signo = SIG_AIO_WRITE;
   full_guy->acb. aio_sigevent.sigev_value.sival_ptr = (void *)full_guy;
   full_guy->state = BUFFER_WRITING; /* ��־������״̬Ϊ����д��*/  
   if (aio_write(&full_guy->acb) < 0) /* �����첽������� */
      perror ( "aio_write" ) ;
   return;
}
main(int argc, char **argv)
{
   int  i, in_file, out_file;
   buffer_t *currentbuf;
   struct sigaction sig_act;
   int chunksize;
   if (argc != 4) {/* ���������� */
      fprintf(stderr, "Usage: %s input-file output-file buf-size-in-Kb\n",
               argv[0]);
      exit(0);
   }
   /* �����������ļ� */
   if ((in_file = open(argv[1], O_RDONLY)) == -1) 
      err_exit(argv[1]);
   if ((out_file = open(argv[2], O_WRONLY|O_CREAT, 0777)) == -1)
      err_exit(argv[2]);
   chunksize=atol(argv[3])*BLOCKSIZE;
    /* ��ʼ������״̬������һ�������ļ��Ļ����� */
   for (i=0; i<NBUFFERS; i++){
      buf_list[i].acb.aio_fildes = out_file;
      buf_list[i].state = BUFFER_FREE;
      buf_list[i].fillpt = 0;
   }
   currentbuf = find_free_buf();
	   /* �����첽I/O����źž�� */
   sigemptyset(&aio_completion_signal);
   sigaddset(&aio_completion_signal, SIG_AIO_WRITE);
   sigemptyset(&sig_act.sa_mask);                  
   sig_act.sa_flags = SA_SIGINFO;
   sig_act.sa_sigaction = aio_ok;
   if (sigaction (SIG_AIO_WRITE, &sig_act, 0) < 0)
      perror("sigaction");
	   /* ��in_file�����ļ���out_file */
   while (1) {
      int nbytes;
again:
      /* ��һ����Ϣ�������� */
      nbytes = read(in_file, currentbuf->buffer+currentbuf->fillpt, 
                      chunksize);
      if (nbytes>0) {
         currentbuf->fillpt += nbytes;
         if (currentbuf->fillpt == BUFFERSIZE) {
            /* д�������Ļ����������һ���»����� */
            flush_filled_buf (currentbuf);
            currentbuf = find_free_buf() ;
         }
      } else if (nbytes == 0) { /* �����ļ�β */
         flush_filled_buf (currentbuf);
         break;
      } else {                  
         if (errno == EINTR) goto again;  /* ���ź��жϣ����¶� */
         else err_exit("read");
      }
   }
   for (i=0; i<NBUFFERS; i++){  /* �ȴ������첽������ */
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
