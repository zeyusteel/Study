#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int ret;
	int fd;
	
	pid = fork();
	if(pid >0)
		exit(0);//父进程正常退出

	pid = setsid(); //创建新会话
	if(pid == -1){
		perror("setsid error");
		exit(1);
	}

	ret = chdir("/Users/zeyu/study/linux/process");//改变工作目录
	if(ret == -1){
		perror("chdir error");
		exit(1);
	}
	
	umask(0022);   //改变文件访问权限掩码

	//已经失去终端控制，再操作 0 1 2 没有意义
	close(STDIN_FILENO);//关闭stdin

	fd = open("/dev/null",O_RDWR);//  /dev/null为新的0号描述符
	if(fd == -1){
		perror("open error");
		exit(1);
	}

	//重定向stdout 和stderr 
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);

	while(1);//模拟守护进程业务

	return 0;
}
