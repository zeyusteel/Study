/*
* Author:wangzeyu
* Date: 2021-05-03
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

#define NUM 5
int queue[NUM];    //全局数组实现环形队列
sem_t blank_num, product_num;     //存放产品格子信号量、产品信号量

void *producer(void *arg)
{
    int i = 0;
    while(1){
        sem_wait(&blank_num);  //生产者等待格子、有的话格子 -1
        queue[i] = rand() % 1000 +1;  //生产一个产品
        printf("Produce : %d\n", queue[i]);
        sem_post(&product_num); //产品 +1

        i = (i+1) % NUM;
        sleep(rand() % 3);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int i = 0;

    while(1){
        sem_wait(&product_num);//消费者等待产品，有的话产品 -1
        printf("Consume : %d\n", queue[i]);
        queue[i] = 0;          //置0 模拟消费
        sem_post(&blank_num);  //格子 +1

        i= (i+1) % NUM;
        sleep(rand() % 3);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t pro,con;

    sem_init(&blank_num,0,NUM);  //初始化格子信号量 = 5
    sem_init(&product_num,0,0);   //初始化产品信号量 = 0

    pthread_create(&pro,NULL,producer,NULL);
    pthread_create(&con,NULL,consumer,NULL);

    pthread_join(pro,NULL);
    pthread_join(con,NULL);

    sem_destroy(&blank_num);
    sem_destroy(&product_num);

    return 0;
}