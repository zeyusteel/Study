#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
	int ret = -1;
	int fd[2];
	pid_t pid;
	int i;

	ret = pipe(fd);
	if(ret == -1){
		perror("pipe error!");
	}

	for(i=0;i<2;i++){
		pid = fork();
		if(pid == -1){
			perror("fork error");
		}
		if(pid == 0)
			break;	
	}

	if(i==2){
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	else if(i == 1){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		perror("wc error");
	}
	else if(i == 0){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
		perror("ls error");
	}

	return 0;	
}
