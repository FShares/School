#include "ch10.h"
#define SET_LOCK(DF,TYPE,OFFSET,WHENCE,LEN)  \
        set_lock(DF,TYPE,OFFSET,WHENCE,LEN,0)
#define SET_LOCK_W(DF,TYPE,OFFSET,WHENCE,LEN)  \
        set_lock(DF,TYPE,OFFSET,WHENCE,LEN,1)
int set_lock(int fd, int type, off_t offset, int whence, off_t len, int w)
{
   struct flock lock; 
   if (type != F_RDLCK && type != F_WRLCK) {
       fprintf(stderr, "illegal lock type\n");
       return -1;
   }
   lock.l_type = type;
   lock.l_whence = whence;
   lock.l_start = offset;
   lock.l_len = len;
   lock.l_pid = -1;
   if(w)   /* 申请并等待直至获得锁 */
       return(fcntl(fd, F_SETLKW, &lock));
   if (fcntl(fd, F_GETLK, &lock) < 0)   // 获取文件的锁信息
       err_exit("F_GETLK failed ");
   if (lock.l_type == F_UNLCK){   // 未置锁，则申请置锁
       lock.l_type = type;   
       return(fcntl(fd, F_SETLK, &lock));
   }
   return -1;	// 已经置锁，再次置锁以失败返回
}
int un_lock (int fd, off_t offset, int whence, off_t len)
{
	struct flock  lock;
	lock.l_type = F_UNLCK;
	lock.l_whence = whence;
	lock.l_start = offset;
	lock.l_len = len;
	return(fcntl(fd, F_SETLK, &lock));
}
