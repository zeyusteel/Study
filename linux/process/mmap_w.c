#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

struct student{
	int id;
	char name[256];
	int age;
};


int main(int argc, char *argv[])
{
	struct student stu = {1,"zeyu",23};
	struct student *p;
	int fd;

	fd = open("test_map",O_RDWR|O_CREAT|O_TRUNC,0644);
	if (fd == -1){
		perror("open error");
		exit(1);
	}
	
	ftruncate(fd,sizeof(stu));

	p = mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p == MAP_FAILED){
		perror("mmap error");
		exit(1);
	}
	
	close(fd);

	while(1){
		memcpy(p,&stu,sizeof(stu));//内存拷贝
		stu.id++;
		sleep(1);
	}
	int ret = munmap(p,sizeof(stu));
	if(ret == -1){
		perror("munmap error");
		exit(1);
	}
	return 0;
}

