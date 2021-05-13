#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <string.h>

int getFileNum(char *path)
{
    DIR *dir = NULL;
    struct dirent *ptr = NULL;

    dir = opendir(path);
    
    if(dir == NULL){
	    perror("opendir");
	    return -1;
    }

    while((ptr = readdir(dir)) != NULL){

        if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
	        continue;

        if(ptr->d_type == DT_DIR){   
            char newpath[128] = {0};
            sprintf(newpath,"%s/%s",path,ptr->d_name);
            printf("-------------------%s\n",newpath); 
            getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG)
            printf("%s\n",ptr->d_name);
    }

    closedir(dir);
    return 0;
    
}
int main(int argc ,char *argv[])
{
    getFileNum(argv[1]);
    return 0;
}
