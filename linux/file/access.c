#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
* Author:wangzeyu
* Date: 2021-05-12
*/

/*
F_OK 值为0，判断文件是否存在
 
X_OK 值为1，判断对文件是可执行权限
 
W_OK 值为2，判断对文件是否有写权限
 
R_OK 值为4，判断对文件是否有读权限
 
注：后三种可以使用或“|”的方式，一起使用，如W_OK|R_OK

*/

int main(void)
{
    int ret;
    if ((ret = access("abc", F_OK)) < 0) {
        printf("error ret = %d\n", ret);
        perror("abc");
        exit(1);
    }
    printf("ret = %d\n", ret);
    printf("abc is exist\n");

    return 0;
}
