#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
* Author:wangzeyu
* Date: 2021-05-22
*/

//字节拼接

unsigned char *cpycpy(unsigned char * old,unsigned int oldlen,unsigned char * new ,unsigned int newlen){
    unsigned int alllen = oldlen+newlen;
    unsigned char * buff = malloc(sizeof(unsigned char)*alllen);
    if(buff==NULL)
        return NULL;
    memset(buff,0,alllen);
    unsigned char *temp = buff;
    int i=0;
    while(i<oldlen){
        *buff++ = *old++;
        i++;
    }
    int j=0;
    while(j<newlen){
        *buff++ = *new++;
        j++;
    }
    return temp;
}

int main(int argc, const char *argv[])
{
    char *pTest = NULL;
    pTest = cpycpy("abcd",4,"1234",5);
    printf("%s\n",pTest);
    return 0;
}