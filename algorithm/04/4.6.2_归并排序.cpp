//利用two pointers 思想 合并两个有序序列
const int maxn = 100;
void merge(int A[],int L1,int R1,int L2,int R2){
    int i = L1;
    int j = L2;
    int temp[maxn], index = 0;
    while(i<=R1&&j<=R2){
        if(A[i]<=A[j]){
            temp[index++] = A[i++];
        }
        else{
            temp[index++] = A[j++];
        }
    }
    //将剩余元素加入temp
    while(j<=R1)
        temp[index++] = A[i++];
    while(j<=R2)
        temp[index++] = A[j++];
    //写回数组A
    for (i = 0; i < index;i++){
        A[L1 + i] = temp[i];
    }
}

void mergeSoft(int A[],int left,int right){
    if(left<right){
        int mid = (left + right) / 2;
        
        mergeSoft(A, left, mid);//递归左子区间
        mergeSoft(A, mid + 1, right);//递归右子区间

        merge(A, left, mid, mid + 1,right); //合并左右子区间
    }
}