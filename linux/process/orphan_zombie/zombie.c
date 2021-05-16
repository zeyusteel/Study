#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//	子进程终止，父进程尚未对子进程进行回收，在此期间，子进程为“僵尸进程”。pcb中还占有位置  kill 对其无效。
int main(int argc,char *argv[])
{
	pid_t pid;
	pid = fork();

	if(pid ==0){
		printf("i am child pid = %d, my parent pid = %d\n",getpid(),getppid());
		sleep(10);
		printf("child goint to die\n");
	}
	else if(pid >0){
		while(1){
			printf("i am parent,pid = %d,my son pid = %d\n",getpid(),pid);
			sleep(1);
		}
	}
	else{
		perror("fork");
		return 1;
	}

	return 0;
}
