/*
* Author:wangzeyu
* Date: 2021-04-25
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct thrd
{
    int var;
    char str[256];
};

void *tfn(void *arg)
{
    struct thrd *val = (struct thrd *)arg;

    val->var = 100;
    
    strcpy(val->str,"hello thread");

    return (void *)val;
}

int main(int argc, const char *argv[])
{
    pthread_t tid;
    struct thrd arg;
    struct thrd *retval = NULL;

    memset(arg.str,0,256);
    int ret = pthread_create(&tid,NULL,tfn,(void *)&arg);
    if(ret != 0){
        fprintf(stderr,"create thread error %s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_join(tid,(void **)&retval);

    if(ret != 0){
        fprintf(stderr,"join error %s\n",strerror(ret));
        exit(1);
    }

    printf("child thread exit with var = %d, str = %s\n",retval->var,retval->str);
    
    pthread_exit(NULL);  //主线程退出其他线程不退出
}