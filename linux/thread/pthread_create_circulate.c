/*
* Author:wangzeyu
* Date: 2021-04-22
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    int i = (int)arg;
    sleep(i);

    if(i == 2){
        pthread_exit(NULL);  //退出当前线程
    }

    printf("this is %d thread pid = %d, tid = %lu\n",i+1,getpid(),pthread_self());
    return NULL;
}

int main(int argc, const char *argv[])
{
    int i;
    int ret;

    pthread_t tid;

    for(i = 0; i < 5; i++){
        ret = pthread_create(&tid, NULL, tfn, (void *)i);    //不能传引用（子线程读i的地址的值时main可能已经给i+1了，造成脏读），这里强转传值
        if(ret != 0){
            fprintf(stderr,"create thread error %s\n",strerror(ret));
            exit(1);
        }
    }

    sleep(i);
    printf("this is main pid = %d, tid = %lu\n",getpid(),pthread_self());
    return 0;
}