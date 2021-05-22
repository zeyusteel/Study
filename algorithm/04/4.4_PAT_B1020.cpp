#include<cstdio>
#include<algorithm>
using namespace std;

struct mooncake{
    double store; //总库存
    double sell; //总售价
    double price;//单价
} cake[1010];

bool cmp(mooncake a,mooncake b){
    return a.price > b.price; //由大到小排序
}

int main()
{
    int n;
    double D;

    scanf("%d%lf", &n, &D);
    for (int i = 0; i < n;i++){
        scanf("%lf", &cake[i].store);
    }
    for (int i = 0; i < n;i++){
        scanf("%lf", &cake[i].sell);
        cake[i].price = cake[i].sell / cake[i].store;
    }
    sort(cake, cake + n, cmp);
    double ans = 0;
    for (int i = 0; i < n;i++){
        if(cake[i].store<=D){
            D -= cake[i].store;
            ans += cake[i].sell;
        }
        else{
            ans += cake[i].price * D;
            break;
        }
    }

    printf("%.2f\n", ans);
    return 0;
}
