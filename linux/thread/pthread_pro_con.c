/*
* Author:wangzeyu
* Date: 2021-05-03
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct msg
{
    int num;
    struct msg *next;
};

struct msg *head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //初始化互斥量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;     //初始化条件变量

int produceNum = 0;
void *producerFun(void *arg)
{
    while(1){
        struct msg * pMsg = malloc(sizeof(struct msg));
        pMsg->num = rand() % 1000 + 1;                  //生产一个数据

        pthread_mutex_lock(&mutex);                     //加锁
        pMsg->next = head;                              //写数据
        head = pMsg;
        printf("produce:%d\n", pMsg->num);
        pthread_mutex_unlock(&mutex);                   //解锁

        pthread_cond_signal(&cond);                     //唤醒阻塞在条件变量cond上的线程


        if(produceNum++ == 30)
            break;
        
        sleep(rand() % 3 + 1);

    }

    return NULL;
}

void *consumerFun(void *arg)
{
    while(1){
        struct msg * pMsg = NULL;
        pthread_mutex_lock(&mutex);                     //加锁
        while(head == NULL){                               //数据为空 这里不能用if 当有多个消费者时，没有拿到产品的消费者还需要继续wait
            pthread_cond_wait(&cond,&mutex);            //阻塞等待条件变量、解锁  被唤醒时再加锁mutex
        }

        pMsg = head;
        head = pMsg->next;                              //读出一个数据
        printf("consume:%d\n", pMsg->num);

        free(pMsg);

        pthread_mutex_unlock(&mutex);                   //解锁

        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    int ret;
    pthread_t producer,consumer;

    srand(time(NULL));

    ret = pthread_create(&producer,NULL,producerFun,NULL);
    if(ret != 0){
        fprintf(stderr,"create thread error : %s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_create(&consumer,NULL,consumerFun,NULL);
    if(ret != 0){
        fprintf(stderr,"create thread error : %s\n",strerror(ret));
        exit(1);
    }

    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    return 0;
}