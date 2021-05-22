#include<iostream>
using namespace std;

int main()
{
    int n;
    int id, score;
    int school[10000] = {0};
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> id >> score;
        school[id] += score;
    }

    int max_id=1, max=0;
    for (int i = 1; i <= n;i++)
    {
        if(school[i]>max)
            {
                max = school[i];
                max_id = i;
            }
    }
    cout << max_id << "  " << max << endl;
    return 0;
}