#include "ch11.h"
int main (void)
{
    pid_t pid;
    int n, mypipe[2];
    char buffer[BUFSIZ+1], some_data[] = "Hello, world!";
    /* �����ܵ� */
    if (pipe (mypipe)) 
        err_exit("Pipe failed.\n");
    /* �����ӽ��� */ 
    if ((pid = fork())==(pid_t)0) { /* �����ӽ��� */
        close(mypipe[1]);     /* �ӽ��̹رչܵ������ */
        n = read(mypipe[0], buffer, BUFSIZ);
        printf("child %d: read %d bytes: %s\n",getpid(),n,buffer);
    } else {   /* ���Ǹ����� */
        close(mypipe[0]);    /* �����̹رչܵ������ */
        n = write(mypipe[1], some_data, strlen(some_data));
        printf("parent %d: write %d bytes: %s\n", getpid(), n, some_data);
    }
    exit (EXIT_SUCCESS);
}
