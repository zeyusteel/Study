#include<stdio.h>
int fun(int n)
{
    if(n==0||n==1)                  //递归边界
        return 1;
    else
        return fun(n - 1) + fun(n - 2);    //递归式
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d",fun(n));
}