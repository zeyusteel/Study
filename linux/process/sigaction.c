#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sig_catch(int sig)
{
	if(sig == SIGINT)
		printf("catch :%d\n",sig);
	else if(sig == SIGQUIT)
		printf("catch :%d\n",sig);
	return;
}

int main(int argc, char * argv[])
{
	struct sigaction act,oldact;
	act.sa_handler = sig_catch;  //设置捕捉回调函数

	sigemptyset(&(act.sa_mask));//清空屏蔽字 ，只在sig_catch 时有效
	act.sa_flags = 0;            //默认值

	int ret = sigaction(SIGINT,&act,&oldact);//注册信号捕捉函数
	if(ret == -1){
		perror("sigaction error");
		return -1;
	}

	ret = sigaction(SIGQUIT,&act,&oldact);
	if(ret == -1){
		perror("sigaction error");
		return -1;
	}

	while(1);
	return 0;
}
