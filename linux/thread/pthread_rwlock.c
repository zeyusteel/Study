/*
* Author:wangzeyu
* Date: 2021-05-02
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int counter;
pthread_rwlock_t rwlock;

void *th_write(void *arg) //写独占
{
    int i = (int)arg;

    while(1){
        pthread_rwlock_wrlock(&rwlock);
        usleep(1000);
        printf("write %d, tid = %lu,counter = %d, ++counter = %d\n",i,pthread_self(),counter,++counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(5000);

    }

    return NULL;
}

void *th_read(void *arg)//读共享
{
    int i = (int)arg;

    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("read %d, tid = %lu,counter = %d\n",i,pthread_self(),counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(1000);

    }
    
    return NULL;
}
int main(int argc, const char *argv[])
{
    int i;
    pthread_t tid[8];

    int ret = pthread_rwlock_init(&rwlock,NULL);
    if(ret != 0){
        fprintf(stderr,"init rwlock error:%s\n",strerror(ret));
        exit(1);
    }

    for(i = 0; i < 3; i++){
        ret = pthread_create(&tid[i],NULL,th_write,(void *)i);
        if(ret != 0){
            fprintf(stderr,"create thread error:%s\n",strerror(ret));
            exit(1);
        }
    }

    for(i = 0; i < 5; i++){
        ret = pthread_create(&tid[i+3],NULL,th_read,(void *)(i+3));
        if(ret != 0){
            fprintf(stderr,"create thread error:%s\n",strerror(ret));
            exit(1);
        }
    }

    for(i = 0; i < 8; i++){
        ret = pthread_join(tid[i],NULL);
        if(ret != 0){
            fprintf(stderr,"join thread error:%s\n",strerror(ret));
            exit(1);
        }
    }

    ret = pthread_rwlock_destroy(&rwlock);
    if(ret != 0){
        fprintf(stderr,"destory rwlock error:%s\n",strerror(ret));
        exit(1);
    }
    return 0;
}