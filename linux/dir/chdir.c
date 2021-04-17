#include <unistd.h>
#include <stdio.h>

int changeDir(char *path)
{
    int ret = chdir(path);
    if(ret == -1){
	perror("chdir");
	return -1;
    }
    return ret;
}

int getCwd()
{
    char buff[128] = {0};
    char *ret = NULL;
    ret = getcwd(buff,sizeof(buff));
    if(ret == NULL){
	perror("getcwd");
	return -1;
    }
    printf("%s\n",buff);
    
    printf("%s\n",ret);
    return 0; 
}
int main(int argc, char *argv[])
{
    printf("%d",changeDir(argv[1]));
    getCwd();
    return 0;
}
