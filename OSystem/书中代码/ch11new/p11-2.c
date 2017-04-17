#include "ch11.h"
int main(void)
{
    int pid, fd[2],len;
    char buffer[PIPE_BUF];
    FILE *stream; 
    if ( pipe(fd) != 0) 
        err_exit("pipe creation failed");
    if ((pid = fork())== 0) { /* �ӽ��� */
        close(fd[1]);            /* ��ʹ�ùܵ���д�� */
        dup2(fd[0],0);           /* �ر�stdin,�ض���ܵ����������stdin */
        close(fd[0]);            /* �ر�����������õ������� */
        /* ��cat������� */
        if (execl("/bin/cat","cat", NULL/*"-n"*/, NULL) == -1)
            err_exit("Unable to run cat"); 
    } else {                      /* ������ */
        close(fd[0]);            /* ��ʹ�ùܵ�������� */
        printf("you can type a line and the line will echoed:\n");
        dup2(fd[1],1);           /* �ر�stdout,�ض���ܵ����������stdout */
        close(fd[1]);
        while (gets(buffer) != NULL)
           puts(buffer);         /* д���ܵ�*/
    }
 } 
