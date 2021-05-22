#include<iostream>
using namespace std;
int main()
{
    int col,row;
    char c;
    cin >> col>>c;
    if (col%2==0)
    {
        row = col / 2;

    }
    else
        row = col / 2 + 1;

    cout << "列" << col << "行" << row << endl;

    for (int i = 0; i < col; i++)
    {
        cout << c;
    }
    cout << endl;

    for (int i = 2; i < row;i++)
    {
        cout << c;
        for (int j = 0; j < col - 2;j++)
        {
            cout << " ";
        }
        cout << c << endl;
    }



    for (int i = 0; i < col; i++)
    {
        cout << c;
    }
}