#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int ret = -1;
	int fd[2];
	pid_t pid;

	ret = pipe(fd);
	if(ret == -1){
		perror("pipe error!");
	}

	pid = fork();
	if(pid == -1){
		perror("fork error");
	}
	else if(pid >0){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		perror("wc error");
	}
	else if(pid == 0){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
		perror("ls error");
	}

	return 0;	
}
