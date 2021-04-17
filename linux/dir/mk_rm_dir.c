#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int makeDir(char *path)
{
    int ret = mkdir(path,0700);
    if(ret == -1){
	perror("mkdir");
	return -1;
    }
    return 0;
}

int delDir(char *path)
{
    int ret = rmdir(path);
    if(ret == -1){
	perror("rmdir");
	return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("%d\n",makeDir(argv[1]));
    printf("%d\n",delDir(argv[1]));
    return 0; 
}
