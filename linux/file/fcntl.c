#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//fcntl： 设置文件属性 阻塞 非阻塞 追加
int main(int argc, char *argv[])
{
    int ret = 0;

    int fd = open("test.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);
    if(fd == -1){
        perror("open");
        return -1;
    }

    if((ret = write(fd,"aaaaa",5)) != 5){
        perror("write");
        return -1;
    }

    int flag = fcntl(fd,F_GETFL,0);
    if(flag == -1){
        perror("fcntl");
        return -1;
    }
    
    printf("old flag :%d  O_APPEND:%d\n",flag,O_APPEND);
    //追加写
    flag |= O_APPEND;
    printf("new flag :%d\n",flag);
    if(fcntl(fd,F_SETFL,flag) == -1){
        perror("fcntl append");
        return -1;
    }

    if((ret = write(fd,"bbbbb",5)) != 5){
        perror("write");
        return -1;
    }

    close(fd);
    return 0; 
}
