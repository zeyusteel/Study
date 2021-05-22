#include<iostream>
using namespace std;
int main(){
    int A, B;
    int D;
    int list[50], num=0;
 
    cin >> A >> B;
    cin >> D;

    int y = A + B;
    do{
        list[num++] = y % D;
        y = y / D;

    } while (y != 0);

    for (int i = num - 1; i >= 0;i--)
    {
        cout << list[i];
    }
    return 0;
}
