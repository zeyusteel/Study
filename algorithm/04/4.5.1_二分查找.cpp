#include <stdio.h>

//A为递增序列
int binarySearch(int *A , int left, int rigth, int x)
{
    int mid;
    while(left <= rigth){
        mid = (left + rigth) / 2;   //容易出现越界   mid = left + (right - left) / 2
        if(A[mid] == x)
            return mid;
        else if(A[mid] > x)
            rigth = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

//函数返回第一个大于等于x的位置
int lower_bound(int *A,int left,int rigth,int x)
{
    int mid;
    while(left<rigth)
    {
        mid = (left + rigth) / 2;
        if(A[mid] >= x)
            rigth = mid;
        else
            left = mid + 1;
    }
    return left;
}

//函数返回第一个大于x的位置
int upper_bound(int *A,int left,int rigth,int x)
{
    int mid;
    while(left<rigth)
    {
        mid = (left + rigth) / 2;
        if(A[mid] > x)
            rigth = mid;
        else
            left = mid + 1;
    }
    return left;
}



 

int main(){

    const int n = 10;
    int A[n] = {1, 3, 4, 6, 7, 8, 10, 11, 12, 15};
    printf("%d  %d\n", binarySearch(A, 0, n - 1, 6), binarySearch(A, 0, n - 1, 9));

}