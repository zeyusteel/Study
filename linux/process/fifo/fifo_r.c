#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}
/*
a. 不使用O_NONBLOCK标志时，只读open要阻塞到某个其它进程为写而打开它为止

b. 不使用O_NONBLOCK标志时，只写open要阻塞到某个其它进程为读而打开它为止
c. 如果在open的时候指定O_NONBLOCK标志，当只读open时，没有进程为写而打开FIFO的话，会返回-1，只写open时，没有进程为读而打开FIFO的话也会返回-1表示失败。

以上的情况使FIFO的使用带来了一些不便，但有一个常用的技巧是，只要用O_RDWR(读写)来打开一个管道，则不会返回失败，而open也不会阻塞。
两个进程使用FIFO来进行通信时，通常会使用两个FIFO，一个用于发送数据(即进行写操作)，一个用于接收数据(即进行读操作)，而这两个FIFO需要均使用O_RDWR来打开。
使用系统调用open, read, write来操作这两个FIFO没有什么问题，程序工作得很好。

*/
int main(int argc, char *argv[])
{
    int fd, len;
    char buf[4096];

    if (argc < 2) {
        printf("./a.out fifoname\n");
        return -1;
    }
    fd = mkfifo(argv[1], 0644);
    //open(fd, ...);
    fd = open(argv[1], O_RDONLY);   // 打开管道文件
    if (fd < 0) 
        sys_err("open");
    while (1) {
        len = read(fd, buf, sizeof(buf));   // 从管道的读端获取数据
        write(STDOUT_FILENO, buf, len);
    //    sleep(3);           //多個读端时应增加睡眠秒数,放大效果.
    }
    close(fd);

    return 0;
}
