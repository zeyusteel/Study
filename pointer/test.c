#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test(char a[])
{
    while(*a != '\0'){
        printf("%c",*a++);
    }
    printf("\n");
    return 0;
}


int testb()
{
	char  a[2][9] = {"abcdefgh","ijklmnop"};
	printf("a = %d  &a = %d\n",a,&a);
    printf("a[0] = %d    %s\n",a[0],a[0]);
    printf("a[1] = %d    %s\n",a[1],a[1]);
	char **p = NULL;
	printf("p = %d   &p = %d\n",p,&p);
    p = a;
	printf("p = %d   &p = %d\n",p,&p);
	printf("*p = %d   %d\n",*p,sizeof(*p));
	char (*s)[9] = NULL;
	printf("%d\n",s);
	s = a;
	printf("*s = %d  %c\n",*s,**s);
    printf("s = %d   %s \n",s,s);
	return 0;
}
int main(int argc, char const *argv[])
{
	testb();
	return 0;
}
