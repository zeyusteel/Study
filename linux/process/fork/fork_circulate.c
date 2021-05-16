#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	pid_t pid;
	for(i = 0;i < 5;i++){
		pid = fork();
		if(pid == -1){
			perror("fork error!");
			exit(1);
		}
		else if(pid == 0){
			break;
		}
	}
	
	if(i<5){
		sleep(i);
		printf(" %d child ,pid = %u,ppid = %u\n",i,getpid(),getppid());	
	}
	else{
		sleep(i);
		printf("i am parent,pid = %u\n",getpid());
	}
}
