#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int pid1, pid2;
    printf("Parent's PID is %d\n", getpid());
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Child1's PID is %d\n", getpid());
        exit(0);
    }
    else if(pid1 < 0)
    {
        printf("fork error!\n");
        exit(1);
    }
    wait(NULL);
    printf("Child1 (PID=%d) already exit\n", pid1);
    pid2 = fork();
    if (pid2 == 0)
    {
        printf("Child2's PID is %d\n", getpid());
        exit(0);
    }
    else if(pid2 < 0)
    {
        printf("fork error!\n");
        exit(1);
    }
    wait(NULL);
    printf("Child2 (PID=%d) already exit\n", pid2);
    return 0;
}