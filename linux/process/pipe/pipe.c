#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int ret;
	int fd[2];
	pid_t pid;
	char *p = "test";

	ret = pipe(fd);
	if(ret == -1){
		perror("pipe error");
	}
	
	pid = fork();
	if(pid == -1){
		perror("fork error");
	}
	else if(pid == 0){
		char buff[1024] = {0};
		close(fd[1]);
		ret = read(fd[0],buff,sizeof(buff));
		write(STDOUT_FILENO,buff,ret);	
	}
	else{
		close(fd[0]);//关闭读
		write(fd[1],p,strlen(p));
		close(fd[1]);
	}
	return 0;
}
