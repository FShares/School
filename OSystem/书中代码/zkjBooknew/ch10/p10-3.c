#include "filelock.h"
int main(void)
{
    int fd;
    off_t fdpos;
    if((fd = open("tempfile", O_RDWR|O_CREAT, 0666)) < 0)    /* 打开文件 */
       err_exit("open error");
    /* 对文件尾及其后的扩充部分置写锁 */
    if (SET_LOCK(fd, F_WRLCK, 0, SEEK_END, 0) == -1) 
       printf("%d set write lock failed\n", getpid());
    else
       printf("%d set write lock success\n", getpid());
    /* 定位文件位置于当前文件尾，并写入8个字符 */
    fdpos = lseek(fd, 0L, SEEK_END);
    write(fd, "8 bytes.", 8);   
    /* 企图释放前面设置的写锁，但实际并未释放，因为文件尾的位置已后移 */
    if (un_lock(fd, 0L, SEEK_END, 0) == -1) 
       err_exit("UN_LOCK error")
    else
       printf("%d un_lock(fd,0,SEEK_END,0) success\n", getpid());
    /* 让子进程在该区域设置读锁验证父进程是否已正确释放其写锁 */
    if (vfork()== 0){   /* 子进程 */
        /* 对整个文件置写锁，不能设置表明父进程有锁区域未释放 */
       if (SET_LOCK(fd, F_WRLCK, 0, SEEK_SET, 0) == -1)
          printf("%d: there are some locks on the file\n",getpid());
       else
          printf("%d: no any locks on the file\n",getpid());
       exit(EXIT_SUCCESS);
    }
    /* 父进程 */
    sleep(5);       /* 保证父进程后退出 */
    exit(EXIT_SUCCESS);
}
