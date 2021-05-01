/*
* Author:wangzeyu
* Date: 2021-04-28
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    while(1){
        //printf("this is thread pid = %d, tid = %lu\n",getpid(),pthread_self());
        pthread_testcancel();//没有进内核的函数需要自己添加取消点
        sleep(1);
    }

    return NULL;
}



int main(int argc, const char *argv[])
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());

    sleep(5);
    ret = pthread_cancel(tid);     //终止线程
    if(ret != 0){
        fprintf(stderr,"pthread_cancel error:%s\n",strerror(ret));
        exit(1);
    }
    
    pthread_exit((void *)0);
}