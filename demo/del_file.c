#include <stdio.h>
#include <stdlib.h>
/*
* Author:wangzeyu
* Date: 2020-12-22
*/
//从文件指定位置删除指定字节

int del_file(const char *fileName,int delpos,int delsize){
    FILE *fp = NULL;
    FILE *new_fp =NULL;
    char *buf = NULL;
    char *frontBuf = NULL;
    int bufsize = 0;
    int frontBufsize = 0;
    int fileSize=0;
    int ret=0;

    if(fileName==NULL)
        return -1;
    
    if(!(fp = fopen(fileName, "r+"))) {
        printf("fileInsert: open %s failed\n", fileName);
        return -1;
    }

    fseek(fp,0,SEEK_END);
    fileSize = ftell(fp);
    fseek(fp,delpos+delsize,SEEK_SET);

    bufsize = fileSize - delpos - delsize;
    if(!(buf = (char*)malloc(bufsize))) {
        printf("fileInsert: malloc failed\n");
        fclose(fp);
        return -1;
    }

    ret = fread(buf,bufsize,1,fp);
    if (ret != 1) {
        printf("read failed !\n");
        free(buf);
        fclose(fp);
        return -1;
    }

    frontBufsize = delpos;
    if(!(frontBuf=(char *)malloc(frontBufsize))){
        printf("fileInsert: malloc failed\n");
        free(buf);
        fclose(fp);
        return -1;
    }

    fseek(fp,0,SEEK_SET);
    ret = fread(frontBuf,frontBufsize,1,fp);
    if(ret!=1){
        printf("read failed !\n");
        free(buf);
        free(frontBuf);
        fclose(fp);
        return -1;
    }

    if(!(new_fp = fopen(fileName, "w+"))) {
        printf("fileInsert: open %s failed\n", fileName);
        return -1;
    }

    fseek(new_fp,0,SEEK_SET);
    ret = fwrite(frontBuf,frontBufsize,1,new_fp);
    if (ret != 1) {
        printf("write failed !\n");
        fileSize = -1;
        goto exit;
    }

    ret = fwrite(buf,bufsize,1,new_fp);
    if (ret != 1) {
        printf("write failed !\n");
        fileSize = -1;
        goto exit;
    }

    fileSize = ftell(new_fp);
    fseek(new_fp,0,SEEK_END);
    int _fileSize = ftell(new_fp);
    if(fileSize != _fileSize)
        fileSize = -1;
    
exit:
    free(buf);
    free(frontBuf);
    fclose(fp);
    fclose(new_fp);
    return fileSize;
}


int main(int argc, char *argv[])
{
    int iRet = del_file(argv[1],5,1);
    printf("%d",iRet);
    return 0;
}
