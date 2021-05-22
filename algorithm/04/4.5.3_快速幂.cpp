#include <cstdio>

typedef long long LL;
LL binaryPow(LL a,LL b,LL m) //递归实现
{
    if(b ==0)
        return 1;
    if(b&1)//b 为奇数，转换为 a*a^b-1
        return a * binaryPow(a, b - 1, m);
    else{//b 为偶数，转换为
        LL mul = binaryPow(a, b / 2, m);
        return mul * mul;
    }
}

LL binaryPow1(LL a,LL b,LL m)//迭代实现
{
    LL ans = 1;
    while(b>0)
    {
        if(b&1){
            ans = ans * a % m;    //ans累积a
        }
        a = a * a % m;  //令a平方
        b >>= 1;  //b右移一位
    }
    return ans;
}