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
    exit(-1);
}

int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if (argc < 2) {
        printf("Enter like this: ./a.out fifoname\n");
        return -1;
    }
    fd = open(argv[1], O_WRONLY);       //打开管道文件
    if (fd < 0) 
        sys_err("open");

    i = 0;
    while (1) {
        sprintf(buf, "hello itcast %d\n", i++);

        write(fd, buf, strlen(buf));    // 向管道写数据
        //sleep(1);
    }
    close(fd);

    return 0;
}
