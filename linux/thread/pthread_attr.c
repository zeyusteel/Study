/*
* Author:wangzeyu
* Date: 2021-05-01
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *tfn(void *arg)
{
    printf("thread tid = %lu, pid = %d\n",pthread_self(),getpid());
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    int ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr,"attr_init error%s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr,"attr_setdetachstate%s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid,&attr,tfn,NULL);
     if(ret != 0){
        fprintf(stderr,"thread_create error%s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr,"attr_destroy error%s\n",strerror(ret));
        exit(1);
    }
    sleep(1);

    ret = pthread_join(tid,NULL);
    if(ret != 0){
        fprintf(stderr,"thread join error%s\n",strerror(ret));
    }

    pthread_exit((void *)0); 
}