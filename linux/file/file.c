#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdio.h>     
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int del_file()
{
    int fd = open("temp",O_CREAT | O_RDWR,0644);
    if(fd == -1){
	    perror("open");
	    return -1;
    }

    int ret = unlink("temp");
    

    int len = write(fd,"deltest",7);
    if(len != 7){
	    perror("write");
	    return -1;
    }

    lseek(fd,0,SEEK_SET);

    char buff[20];
    memset(buff,0,20);
    int rlen = read(fd,buff,sizeof(buff));
    if(rlen<0){
        perror("read");
        return -1;
    }

    int wlen = write(1,buff,rlen);
    if(wlen != rlen){
        perror("write");
        return -1;
    }

    close(fd);
    return 0;
}
int read_write()
{
    int fd;
    int new_fd;
    char *buff;
    int bufSize;

    fd = open("test.txt",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    } 

    new_fd = open("new_test.txt",O_CREAT | O_WRONLY,0644);
    if(new_fd == -1)
    {
        perror("open");
        return -1;
    }

    buff = malloc(sizeof(char)*1024);
    int count = read(fd,buff,/*sizeof(buff)*/7);
    if(count ==-1 ){
        perror("read");
        return -1;
    }

    while(count){
        int ret = write(new_fd,buff,count);
        printf("write byte %d\n",ret);
        
        count = read(fd,buff,sizeof(buff));
        printf("%d\n",count);
    }

    free(buff);
    close(fd);
    close(new_fd);
    return 0;
}

int openFile()
{
    int fd;
	//打开文件	
    fd = open("can not found ",O_RDWR);
    if(fd == -1){
	    perror("open file");
	    exit(1);
    }
    close(fd);
    return 0;
}

int createFile()
{
    int fd;
    //创建新文件
    fd = open("make_new_file",O_RDWR | O_CREAT,777);
    if(fd == -1){
	    perror("open file");
       // exit(1);
    }
    //关闭文件
    int ret = close(fd);
        printf("ret = %d\n",ret);
    if(ret == -1)
    {
	    perror("close file");
	    exit(1);
    }
    return 0;

}

int verifyFileExit()
{
    int fd;
    //判断文件是否存在	
    fd = open("make_new_file",O_RDWR | O_CREAT | O_EXCL,777);
    if(fd == -1){
        perror("open file");
        //exit(1);
    }
    //关闭文件
    int ret = close(fd);
    printf("ret = %d\n",ret);
    if(ret == -1)
    {
	    perror("close file");
	    exit(1);
    }
    return 0;

}

int cutFile()
{
    int fd;
    //文件截断为0
    fd = open("make_new_file",O_RDWR | O_TRUNC);
    if(fd == -1){
	    perror("open file");
	    exit(1);
    }
    //关闭文件
    int ret = close(fd);
    printf("ret = %d\n",ret);
    if(ret == -1)
    {
	    perror("close file");
	    exit(1);
    }
    return 0;
}
int main(int argc , char *argv[])
{
   // int ret = del_file();
   // printf("%d\n",ret);

    del_file();
    return 0;
}
