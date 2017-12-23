#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (void){
	pid_t pid;
	pid_t pid2;
    // printf("Parent's PID is %d\n", getpid());
	if((pid = fork()) > 0){
		/*parent process*/
    	// printf("fork ()Parent's PID is %d\n", getpid());
		printf("1\n");
		if((pid2 = fork()) == 0){
			/*child process*/
			printf("3\n");
			exit(0);
		}
		// exit(0);
	}else if(pid == 0){
		/*child process*/
		printf("2\n");
		exit(0);
	}else{
		printf("fork error\n");
		exit(1);
	}
	return 0;
}