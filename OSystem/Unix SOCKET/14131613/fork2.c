#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (void){
	pid_t pid;
	int status;
	if((pid = vfork()) == 0){
		/*child process*/
		printf("hello");
		exit(0);
	}else if(pid > 0){
		/*parent process*/
		printf("word\n");
		exit(0);
	}else{
		printf("fork error\n");
		exit(0);
	}
	return 0;
}