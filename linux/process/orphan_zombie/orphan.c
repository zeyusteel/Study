#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
/*
* Author:wangzeyu
* Date: 2021-05-14
*/

//父进程先于子进终止，子进程沦为“孤儿进程”，会被 init 进程领养。

int main(int argc,char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == 0){
		while(1){
			printf("i am child pid = %d,parent pid = %d\n",getpid(),getppid());
			sleep(1);
		}
	}
	else if(pid > 0 ){
		printf("i am parent pid = %d",getpid());
		sleep(9);
		printf("parent going to die\n");
	}
	else{
		perror("fork error");
		exit(1);
	}
	
	return 0;
}
