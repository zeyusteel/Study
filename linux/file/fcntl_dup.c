#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
/*
* Author:wangzeyu
* Date: 2021-05-12
*/
//dup 和dup2区别在于dup2可以指定新的描述符 dup2(old_fd,new_fd);如果new_fd打开，则会先将其关闭，如果new_fd = old_fd，直接返回new_fd
int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("open error");
        exit(1);
    }
    printf("fd1 = %d\n",fd1);

    int fd2 = fcntl(fd1, F_DUPFD, 0);   // 等于 dup(fd1)  0 ：复制一个最小的可用的描述符
    if (fd2 < 0) {
        perror("fcntl error");
        exit(1);
    }
    printf("fd2 = %d\n",fd2);

    int fd3 = fcntl(fd1, F_DUPFD, 18); //等于 dup2(fd1,18)  18:复制一个大于18的可用的描述符
    if (fd3 < 0) {
        perror("fcntl error");
        exit(1);
    }

    printf("fd3 = %d\n",fd3);

    char buf[10] = {0};

    int n = read(fd3, buf, 10);
    if (n < 0) {
        perror("read error"); 
        exit(1);
    }

    printf("%d read:%s\n", fd3, buf);
    printf("--------------------\n");

    close(fd1);
    close(fd2);
    close(fd3);
	return 0;
}
