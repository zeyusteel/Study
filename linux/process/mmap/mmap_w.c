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
/*
	strcpy和memcpy主要有以下3方面的区别。
1、复制的内容不同。strcpy只能复制字符串，而memcpy可以复制任意内容，例如字符数组、整型、结构体、类等。
2、复制的方法不同。strcpy不需要指定长度，它遇到被复制字符的串结束符"\0"才结束，所以容易溢出。memcpy则是根据其第3个参数决定复制的长度。
3、用途不同。通常在复制字符串时用strcpy，而需要复制其他类型数据时则一般用memcpy。
*/
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

