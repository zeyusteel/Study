#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

void catch_child(int signo)//有子进程终止，发送sigchild信号，该函数会被内核回调
{
	pid_t wpid;
	int status;

	while((wpid = waitpid(-1,&status,0)) != -1){//循环回收，防止僵尸进程 
		if(WIFEXITED(status))
			printf("catch child id %d,ret = %d\n",wpid,WEXITSTATUS(status));
	}
	
	return;
}

int main(int argc, char *argv[])
{
	pid_t pid;

	//阻塞
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,NULL);

	int i;
	for(i = 0;i<5;i++)
		if((pid = fork()) == 0)
			break;
	
	if(i == 5){
		struct sigaction act;
		act.sa_handler = catch_child;//设置回调函数
		sigemptyset(&act.sa_mask);//设置捕捉函数执行期间屏蔽字
		act.sa_flags = 0;//设置默认属性，本信号自动屏蔽

		sigaction(SIGCHLD,&act,NULL);//注册信号捕捉函数

		//解除阻塞
		sigprocmask(SIG_UNBLOCK,&set,NULL);//如果不解除阻塞，回调函数无法执行
		printf("i am parent,pid = %d\n",getpid());

		while(1);               //模拟父进程后续逻辑
	}
	else{
		printf("i am child pid = %d\n",getpid());
		return i;	
	}	
	
	return 0;
}
