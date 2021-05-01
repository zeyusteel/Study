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
    printf("this is thread pid = %d, tid = %lu\n",getpid(),pthread_self());


    return (void *)(15);
}



int main(int argc, const char *argv[])
{
    pthread_t tid;
    void *retVal;
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_detach(tid);
    if(ret != 0){
        fprintf(stderr,"pthread_detach error:%s\n",strerror(ret));
        exit(1);
    }

    sleep(1);
    ret = pthread_join(tid,&retVal);     //捕捉
    if(ret != 0){
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }

    printf("main pid = %d, tid = %d ret = %d\n",getpid(),pthread_self(),(int)(retVal));
    
    pthread_exit((void *)0);
}