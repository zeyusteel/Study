#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *p;
	pid_t pid;

	int fd;

	fd = open("mmap_fork",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd < 0){
		perror("open error");
		return -1;
	}

	ftruncate(fd,10);
	//	p = (int *)mmap(NULL, 40, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	p = (char *)mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p == MAP_FAILED){
		perror("mmap error");
		return -1;
	}
	close(fd);

	pid = fork();
	if(pid == 0){
		strcpy(p,"hello map");
	}
	else if(pid > 0){
		sleep(1);
		printf("%s\n",p);
		wait(NULL);

		int ret = munmap(p,10);
		if(ret == -1){
			perror("munmap error");
			return -1;
		}
	}
	else{
		perror("fork error");
	}
	
	return 0;
}
