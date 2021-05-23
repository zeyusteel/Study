#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>


/*
* Author:wangzeyu
* Date: 2021-05-23
*/
//关于指针

const char* fun(){
    printf("test\n");
    return "abc";
}

int main(int argc, const char *argv[])
{
//指针变量 = 地址变量
#if 0
    int a = 5;
    int *p = &a;
    printf("%u\n", (unsigned int)p);
#endif

//需要赋值并初始化
#if 0
    int *pErr;
    *pErr = 5;//错误用法！
#endif


//指针在c中常与回调函数、字符串、字符数组、结构体一起使用，这里简单介绍一下

//01函数
//指向函数的指针变量与返回指针的函数，这里就简单写一起了
#if 0 
    const char* (*pFun)();
    const char *pRet = NULL;    //注意区分指针常量与常量指针
    pFun = fun;                 //函数名与数组名一样 都是地址常量
    pRet = pFun();
    printf("%s\n", pRet);

#endif

//02字符数组
//简单介绍一下二维字符数组与行列指针

    char  a[][5] = {"abcd","1234"};
    printf("%s\n", a[0]);
    printf("%s\n", a[1]);
    printf("a = %u  &a = %u  a[0] = %u &a[0] = %u\n",
    (unsigned int)a, (unsigned int)&a, (unsigned int)a[0], (unsigned int)&a[0]);

    //a 是数组的首地址，元素的首地址，是地址常量，而且还是一个行指针；
    printf("%s\n",(char *)(a+1));
    char (*pH)[5] = a;
    printf("%s\n", (char *)pH);
    printf("%s\n", (char *)(pH+1));

    //而[]与*都会将行指针变为列指针，即元素指针
    printf("%s\n", a[0] + 1); //a[0][1]的地址
    printf("%s\n", (*a) + 1);

    //而现在就会指向地址的值
    printf("%c\n", a[0][1]);
    printf("%c\n", *((*a) + 1));

    printf("===================\n");
    //这也是为什么用以下方法去指向二维字符数组会错误
#if 0
    char **test = NULL;
    test = a;
    printf("%s",*test);
#else
    //注意区分字符数组与指针数组
    char **test = NULL;
    char  *arr[3] = {"abcd","1234",NULL};
    test = arr;
    printf("%s\n",*test);
    printf("%u %u\n",(unsigned int)arr,(unsigned int)(arr+1));
    printf("%s %u\n",arr[0],(unsigned int)arr[0]);
    printf("%s %u\n",arr[1],(unsigned int)arr[1]);
    printf("%u %s\n",(unsigned int)*test,*test);
    printf("%u %s\n",(unsigned int) *(test+1), *(test+1));
#endif
//03 结构体指针
    //其实与普通指针没什么区别，指针指向一个结构体而已
    //具体用法以我在日志工具中写的判断文件权限的函数为例

    int check_authority(const char *pPath);
    int iRet = check_authority(argv[1]);
    printf("return val: %d\n",iRet);

    return 0;
}

int check_authority(const char *pPath)
{
    int iRet = 0;
    struct stat stStat;
    uid_t uid;

    //******************************
    struct passwd *pPwd = NULL;
    struct group *pGrp = NULL;
    struct group *pFileGrp = NULL;
    char ** pGroupMember;
    //******************************


    uid = getuid();
    pPwd = getpwuid(uid);
    if(!pPwd){
        fprintf(stderr,"can not find user uid = %d\n",(int)uid);
        return -1;
    }

    pGrp = getgrgid(pPwd->pw_gid);
    if(!pGrp){
        fprintf(stderr,"can not find group gid = %d\n",(int)pPwd->pw_gid);
        return -1;
    }



    iRet = stat(pPath,&stStat);
    if(iRet == -1){
        fprintf(stderr,"stat error\n");
        return -1;
    }

    if(!S_ISREG(stStat.st_mode)){
        fprintf(stderr,"not a file!\n");
        return -1;
    }

    if((stStat.st_uid == uid) && (stStat.st_mode & S_IRUSR)){
        printf("can read as owner\n");
        return 0;
    }

    if(stStat.st_mode & S_IRGRP){

        pFileGrp = getgrgid(stStat.st_gid);
        if(!pFileGrp){
            fprintf(stderr,"can not find group gid = %d\n",(int)stStat.st_gid);
            return -1;
        }

        pGroupMember = pFileGrp->gr_mem;
        while(*pGroupMember){
            iRet =strcmp(*pGroupMember,pPwd->pw_name);
            if(iRet == 0){
                printf("can read as group member :%s\n",*pGroupMember);
                return 0;
            }
            pGroupMember++;
        }

    }

    if(stStat.st_mode & S_IROTH){
        printf("can read as other\n");
        return 0;
    }
    printf("can not read  %s by %s\n",pPath,pPwd->pw_name);
    return -1;
}