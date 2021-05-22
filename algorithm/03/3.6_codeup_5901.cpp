//回文串
#include<cstdio>
#include<cstring>
const int maxn = 256;
bool fun(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len /2;i++)
    {
        if(str[i]!=str[len-1-i])
            return false;
    }
    return true;
}


int main ()
{
    char str[maxn];
    fgets(str,255);
    if(fun(str)==true)
        printf("Y");
    else
        printf("N");
    

    return 0;
}