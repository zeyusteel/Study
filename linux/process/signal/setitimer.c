#include <sys/time.h>
#include <stdio.h>

#include <signal.h>

void myfunc(int sig)
{
	printf("signal !\n");
}
int main(int argc, char * argv[])
{
	struct itimerval it, oldit;
	signal(SIGALRM,myfunc);

	it.it_value.tv_sec = 2;
	it.it_value.tv_usec = 0; //微秒

	it.it_interval.tv_sec = 5; //轮询5s
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&it,&oldit) == -1){
		perror("setitimer error");
		return -1;
	}
	
	while(1);
	return 0;
}
