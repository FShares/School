#include "filelock.h"
int main(void)
{
    int fd;
    off_t fdpos;
    if((fd = open("tempfile", O_RDWR|O_CREAT, 0666)) < 0)    /* ���ļ� */
       err_exit("open error");
    /* ���ļ�β���������䲿����д�� */
    if (SET_LOCK(fd, F_WRLCK, 0, SEEK_END, 0) == -1) 
       printf("%d set write lock failed\n", getpid());
    else
       printf("%d set write lock success\n", getpid());
    /* ��λ�ļ�λ���ڵ�ǰ�ļ�β����д��8���ַ� */
    fdpos = lseek(fd, 0L, SEEK_END);
    write(fd, "8 bytes.", 8);   
    /* ��ͼ�ͷ�ǰ�����õ�д������ʵ�ʲ�δ�ͷţ���Ϊ�ļ�β��λ���Ѻ��� */
    if (un_lock(fd, 0L, SEEK_END, 0) == -1) 
       err_exit("UN_LOCK error")
    else
       printf("%d un_lock(fd,0,SEEK_END,0) success\n", getpid());
    /* ���ӽ����ڸ��������ö�����֤�������Ƿ�����ȷ�ͷ���д�� */
    if (vfork()== 0){   /* �ӽ��� */
        /* �������ļ���д�����������ñ�����������������δ�ͷ� */
       if (SET_LOCK(fd, F_WRLCK, 0, SEEK_SET, 0) == -1)
          printf("%d: there are some locks on the file\n",getpid());
       else
          printf("%d: no any locks on the file\n",getpid());
       exit(EXIT_SUCCESS);
    }
    /* ������ */
    sleep(5);       /* ��֤�����̺��˳� */
    exit(EXIT_SUCCESS);
}
