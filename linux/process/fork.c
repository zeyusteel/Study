#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("start\n");
	pid_t pid;
	pid = fork();
	if(pid == -1){
		perror("fork error!!");
		exit(1);
	}
	else if(pid == 0){
		printf("child pid = %u,ppid = %u\n",getpid(),getppid());//打印pid和父进程pid
	}
	else{
		printf("parent pid = %u,ppid = %u\n",getpid(),getppid());
		sleep(1);//父进程后结束
	}

	printf("end\n");
	return 0;
	
}
