#include<iostream>
using namespace std;
int main()
{
    int z[50];
    int num = 0;
    int y,P;
    cout << "输入数值和进制";
    cin >> y;
    cin >> P;
    do{
        z[num++] = y % P;
        y = y / P;
    }while(y!=0);//这里不用while(){} 如果y=0会直接跳出


    for (int i = num - 1; i >= 0;i--)
    {
        cout << z[i];
    }
    return 0;

}