#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	}
	else if (pid > 0){
		while(1){
			printf("parent pid = %d\n",getpid());
			sleep(1);
		}
	}
	else{
		printf("parent pid = %d child pid = %d\n",getppid(),getpid());
		kill(getppid(),SIGCHLD);
	}
	return 0;
}
