#include "ch10.h"

int input_timeout(int filedes, unsigned int seconds)
{
    fd_set set;
    struct timeval timeout;
    int n;
    char buf[1024];

    FD_ZERO(&set);             /* ��ʼ�ļ������ּ��� */
    FD_SET(filedes, &set);
    timeout.tv_sec = seconds;  /* ��ʼtimeout���ݽṹ */
    timeout.tv_usec = 0;

    /* selectʱ�䵽�ڷ���0�������������1�����ִ��󷵻�-1 */
again:
    if ((n = select(FD_SETSIZE, &set, NULL, NULL, &timeout)) < 0) { //���ִ���
        if (errno = EINTR) 
            goto again;
    }
    else if (n > 0) {   //�������
        n = read(filedes,buf,sizeof(buf));
        printf("read data:  %s\n",buf);
    }
    else  //ʱ�䵽��
        printf("tiomeout for select\n");
    return n;
}

int main (void)
{
    fprintf(stderr, "select returned %d.\n",input_timeout(STDIN_FILENO, 5));
    return 0;
}
