//进制转换

#include<iostream>
using namespace std;
int main()
{
    //将P进制数转换成十进制
    int y = 0, product = 1;
    int x,P;
    cout << "输入数字和进制";
    cin >> x;
    cin >> P;
    while(x!=0)
    {
        y = y + (x % 10) * product;
        x = x / 10;
        product = product * P;
    }
    cout <<P<<"进制转为10进制:"<< y;
}       