#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
	pid_t pid,wpid;
	pid = fork();
	int status;

	if(pid ==0){
		printf("i am child , my parent pid = %d\n",getppid());
		sleep(10);
		printf("child goint to die\n");
		return 35;// 或exit(35)
	}
	else if(pid >0){
		wpid = wait(&status);
		if(wpid == -1){
			perror("wait error");
			exit(1);
		}
		//正常结束
		if(WIFEXITED(status)){
			printf("child exit with %d\n",WEXITSTATUS(status));//获得进程退出的状态
		}
		//被信号中断结束
		if(WIFSIGNALED(status)){
			printf("child killed by %d\n",WTERMSIG(status));//获得使进程终止的那个信号的编号
		}	

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
