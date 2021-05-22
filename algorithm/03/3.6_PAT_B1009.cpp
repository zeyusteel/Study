#include<cstdio>
#include<cstring>
const int maxn = 80;
int main()
{
    char str[maxn];
    gets(str);
    int len = strlen(str);
    int r = 0, h = 0;//r:行 h:列
    char ans[90][90];
    for (int i = 0; i < len;i++)
    {
        if(str[i]!=' ')
        {
            ans[r][h++] = str[i];
        }
        else
        {
            ans[r][h] = '\0';
            r++;
            h = 0;
        }
    }
    for (int i = r; i >= 0;i--)
        {
            printf("%s", ans[i]);
            if (i > 0)
                printf(" ");
        }
        return 0;
}