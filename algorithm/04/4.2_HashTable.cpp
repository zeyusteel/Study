#include<cstdio>
const int maxn = 100010;
bool hashTable[maxn] = {false};
//散列 用空间换时间  时间复杂度    O（m+n）
int main()
{
    int n, m, x;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n;i++)
    {
        scanf("%d", &x);
        hashTable[x] = true;
    }
    for (int i = 0; i < m;i++)
    {
        scanf("%d", &x);
        if(hashTable[x]==true)
            printf("YES\n");
        else
        {
            printf("NO\n");
        }
        
    }
}
