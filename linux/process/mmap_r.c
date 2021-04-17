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
	struct student stu; 
	struct student *p;
	int fd;

	fd = open("test_map",O_RDONLY,0644);
	if (fd == -1){
		perror("open error");
		exit(1);
	}
	

	p = mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);
	if(p == MAP_FAILED){
		perror("mmap error");
		exit(1);
	}
	
	close(fd);

	while(1){
		printf("id = %d,name = %s,age=%d\n",p->id,p->name,p->age);
		sleep(1);
	}
	int ret = munmap(p,sizeof(stu));
	if(ret == -1){
		perror("munmap error");
		exit(1);
	}
	return 0;
}

