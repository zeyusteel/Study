#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Partition(int A[],int left,int right){
    int temp = A[left];
    while(left<right){
        while(left<right && A[right]>temp)
            right--;
        A[left] = A[right];
        while(left<right && A[left]<=temp)
            left++;
        A[right] = A[left];
    }
    A[left] = temp;
    return left;
}

void quickSoft(int A[], int left, int right)
{
    if(left < right){
        int pos = Partition(A, left, right);
        quickSoft(A, left, pos - 1);
        quickSoft(A, pos + 1, right);
    }
}


//随机数
int main()
{
    srand((unsigned)time(NULL));
    printf("%d", rand() * 1.0 / RAND_MAX * 50000);
    return 0;
}