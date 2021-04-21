/*
* Author:wangzeyu
* Date: 2021-04-21
*/
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu\n",getpid(),pthread_self());
    return NULL;
}


int main(int argc, const char *argv[])
{
    pthread_t tid;

    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        perror("pthread error!");
        exit(1);
    }
    printf("thread: pid = %d, tid = %lu\n",getpid(),pthread_self());
    sleep(1);
    return 0;
}