#include<cstdio>
#include<iostream>
using namespace std;

const int MAX = 500010; 
int nums[MAX];

void merge(int lo, int mi, int hi){
    int* A = &nums[lo];
    int lengthB = mi - lo;
    int* B = new int[lengthB];
    for(int i = 0; i < lengthB; i++){
        B[i] = A[i];
    }
    int lengthC = hi - mi;
    int* C = &nums[mi];
    for(int i = 0, j = 0, k = 0; (j<lengthB)||(k<lengthC);){
        if ( ( j < lengthB ) && ( ! ( k < lengthC ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++];
        if ( ( k < lengthC ) && ( ! ( j < lengthB ) || ( C[k] <  B[j] ) ) ) A[i++] = C[k++];
    }
    delete []B;
}

void mergeSort(int lo, int hi){ //[lo, hi)
    if(hi - lo < 2) return;
    int mi = (hi + lo) /2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

int binsearch(int obj, int lo, int hi){
    while(lo < hi){
        int mi= (lo+hi)>>1;
        (obj<nums[mi])? hi = mi : lo = mi + 1;
    }
    // cout<<lo<<endl;
    return --lo; ////循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
}

int main(){
    int n, m; // n: the number of node, m: the number of searching
    int a, b; // [a,b]: the searching interval
    int left, right; // index of maxnum <= a
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    mergeSort(0,n);

    for(int i = 0; i<m; i++){
        scanf("%d%d",&a, &b);
        left = binsearch(a-1, 0, n);
        right = binsearch(b, 0, n);
        printf("%d\n",right-left);
    }
    // for(int i = 0; i < MAX; i++){
    //     cout<<nums[i]<<" ";
    // }
    return 0;
}


/*
5 2
1 3 7 9 11
4 6
7 12
*/

/*
0
3
*/