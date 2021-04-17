#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int fd;
	fd = open("ps.out",O_WRONLY|O_CREAT|O_TRUNC,0644);
	if(fd <0){
		perror("open ps.out error");
		exit(1);
	}

	dup2(fd,STDOUT_FILENO);  //让标准输出指向fd
	execlp("ps","ps","a",NULL);//exec调用成功就去执行新的程序，不返回值；失败返回值-1

	perror("exec error");
	exit(1);

	return 0;
}
