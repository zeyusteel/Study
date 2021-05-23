#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int check_authority(const char *pPath)
{
    int iRet = 0;
    struct stat stStat;
    uid_t uid;
    struct passwd *pPwd = NULL;
    struct group *pGrp = NULL;
    struct group *pFileGrp = NULL;
    char ** pGroupMember;

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


int main(int argc,char *argv[])
{
    int iRet = check_authority(argv[1]);
    printf("return val: %d\n",iRet);
    return 0;
}
