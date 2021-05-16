#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void print_set(sigset_t *set)
{
	int i;
	for(i=1; i<32; i++){
		if(sigismember(set,i))//判断一个信号是否在集合中
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	sigset_t set, oldset,pedset;
	int ret = 0;

	sigemptyset(&set);      //清空
	sigaddset(&set,SIGINT); //添加信号

	ret = sigprocmask(SIG_BLOCK,&set,&oldset);  //覆盖阻塞信号集
	if(ret == -1){
		perror("sigprocmask error");
		exit(1);
	}


	while(1){
		ret = sigpending(&pedset);  //获取未决信号集
		if(ret == -1){
			perror("sigpending error");
			exit(1);
		}
		
		print_set(&pedset);
		sleep(2);
	}
	return 0; 
}
