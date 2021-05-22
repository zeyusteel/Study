#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Student {
    char id[15];
    int score;
} stu[10];
bool cmp(Student a,Student b)
{
    if (a.score!=b.score)
        return a.score > b.score;
    else
        return strcmp(a.id, b.id) < 0;
}

int main()
{
    strcpy(stu[0].id, "01");
    strcpy(stu[1].id, "02");
    strcpy(stu[2].id, "03");
    stu[0].score = 79;
    stu[1].score = 99;
    stu[2].score = 99;
    sort(stu, stu + 3, cmp);
    for (int i = 0; i < 3;i++)
    {
        printf("%s,%d  \n", stu[i].id, stu[i].score);
    }
        return 0;
}

