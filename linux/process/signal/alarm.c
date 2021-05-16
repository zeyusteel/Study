#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void test(int sig){
	printf("-----------------signal :%d\n", sig);
}

int main(int argc, char *argv[])
{
	int i = 0;
	//signal(SIGALRM,test);
	alarm(1);//定时一秒，默认处理会结束进程

	while(1){
		printf("%d\n",i++);
	}
	return 0;
}
