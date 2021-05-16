#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void test(int arg){
	printf("test : %d\n",arg);
}

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
			signal(SIGCHLD,test);
			sleep(1);
		}
	}
	else{
		printf("parent pid = %d child pid = %d\n",getppid(),getpid());
		kill(getppid(),SIGCHLD);//子进程结束会发送一次SIGCHLD，kill会发一次SIGCHLD
	}
	return 0;
}
