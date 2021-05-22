#include <cstdio>
#include <cmath>

//计算根号2的近似值
const double eps = 1e-5;
double f(double x){
    return x * x;
}

double calSqrt(){
    double left = 1, right = 2, mid = 0;
    while(right-left > eps){
        mid = (left + right) / 2;
        if(f(mid)>2)
            right = mid;
        else
            left = mid;
    }
    return mid;
}

//给定R 、 r求注入水的高度h
const double PI = acos(-1.0); //PI
//r = f(h),r关于h递增
double r_f(double R,double h)
{
    double alpha = 2 * acos((R - h) / R);
    double L = 2 * sqrt(R * R - (R - h) * (R - h));
    double S1 = alpha * R * R / 2 - L * (R - h) / 2;
    double S2 = PI * R * R / 2;
    return S1 / S2;
}

double solve(double R,double r)
{
    double left = 0, right = R, mid=0;  //[left,right] = [0,R]
    while(right-left>eps){
        mid = (left + right) / 2;
        if(r_f(R,mid) > r)
            right = mid;
        else
            left = mid;
    }
    return mid;
}

int main(){

    double R = 2.0;
    double r = 0.7;
    printf("%.4f\n", solve(R, r));
    return 0;
}