#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == -1){
		perror("fork failed");
		exit(1);
	}
	else if(pid > 0){
		sleep(1);
		printf("i am parent\n");	
	}
	else{
	//	execlp("ls","ls","-l","-a",NULL);//需要借助环境变量
		execl("/bin/ls","ls","-l","-a",NULL);//路径
	}
	return 0;
}
