/*
* Author:wangzeyu
* Date: 2021-05-01
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex;

void *tfn(void *arg)
{
    srand(time(NULL));
    while(1){
        pthread_mutex_lock(&mutex);   //加锁 --mutex
        printf("hello ");
        sleep(rand() % 3);
        printf("world\n");
        pthread_mutex_unlock(&mutex);  //解锁  ++mutex

        sleep(rand() % 3);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t tid;
    srand(time(NULL));

    int ret = pthread_mutex_init(&mutex,NULL);    //mutex = 1
    if(ret != 0){
        fprintf(stderr,"mutex init error %s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        fprintf(stderr,"create error %s\n",strerror(ret));
        exit(1);
    }

    while(1){
        pthread_mutex_lock(&mutex);   //加锁
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);  //解锁

        sleep(rand() % 3);    
    }

    ret = pthread_join(tid,NULL);
    if(ret != 0){
        fprintf(stderr,"create error %s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_mutex_destroy(&mutex);
    if(ret != 0){
        fprintf(stderr,"mutex destory error %s\n",strerror(ret));
        exit(1);
    }
    return 0;
}