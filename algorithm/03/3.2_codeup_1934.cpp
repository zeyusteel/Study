#include<iostream>
using namespace std;
int main()
{
    int num[100];
    int n;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        int a;
        cin >> a;
        num[i] = a;
    }
    int x;
    cin >> x;
    for (int i = 0; i < n;i++)
    {
        if(num[i]==x)
        {
            cout << i << endl;
            break;
        }
    }

        return 0;
}