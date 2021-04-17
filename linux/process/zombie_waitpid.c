#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i;
	pid_t pid,w_pid,target_pid;
	int status;

	for(i = 0;i < 5;i++){
		pid = fork();
		if(pid == -1){
			perror("fork error!");
			exit(1);
		}
		else if(pid == 0){
			break;
		}
		if(i == 3){
			target_pid = pid;
		}
	}
	
	if(i<5){
		sleep(i);
		printf(" %d child ,pid = %u,ppid = %u\n",i,getpid(),getppid());	
	}
	else{
		sleep(i);
	//	w_pid = waitpid(target_pid,&status,0);
	//	printf("recover pid %d\n",w_pid);
		while(waitpid(-1,&status,0)>0);
		printf("i am parent,pid = %u\n",getpid());
		while(1);
	}
}
