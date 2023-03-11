#include<iostream>
#include<cstdio>
#define MAXN 4000001
struct lightHouse{
    int x;
    int y;
}point[MAXN],left[MAXN],right[MAXN];

long long merge(lightHouse* point, int l, int m, int r, int xORy){
    if(r-l<1) return 0;
    // std::cout<<l<<m<<r<<std::endl;
    int leftLen = m-l;
    int rightLen = r-m;
    long long counter = 0;

   for(int i = 0; i < leftLen; i++){
        left[i] = point[i+l]; //?
        // std::cout<<"left"<<i<<":"<<left[i].x<<left[i].y<<std::endl;
        // std::cout<<"point"<<i+l<<":"<<point[i+l].x<<point[i+l].y<<std::endl;
    }
    for(int j = 0; j < rightLen; j++){
        right[j] = point[j+m]; //?
        // std::cout<<"right"<<j<<":"<<right[j].x<<right[j].y<<std::endl;
        // std::cout<<"point"<<j+m<<":"<<point[j+m].x<<point[j+m].y<<std::endl;
    }
    int i = 0, j = 0, k = l;
    while(i < leftLen && j < rightLen){
        if(xORy == 0){// sort by x;
            if(left[i].x <= right[j].x){
                point[k++] = left[i++];
            }
            else{
                point[k++] = right[j++];
            }   
        }else{ // sort by y, and count;
            if(left[i].y <= right[j].y){
                point[k++] = left[i++];
                counter += r-(m+j);
                // std::cout<<"counter"<<":"<<r-(m+j)<<std::endl;
            }
            else{
                point[k++] = right[j++];
            }   
        }
    }
    while(i < leftLen){
        point[k++] = left[i++];
    }
    while(j < rightLen){
        point[k++] = right[j++];
    }
    return counter;
}

long long mergeSort(lightHouse* point, int l, int r, int xORy){
    long long counter = 0; 
    if (r-l<2) return 0; //r-l==1就是单元素
    int m = (l+r)/2; 
    counter += mergeSort(point, l, m, xORy);  //这里采用的是开区间
    counter += mergeSort(point, m, r, xORy); 
    counter += merge(point, l, m, r, xORy); 
    return counter; 
}

int main(){
    int n; // 灯塔数量
    int x, y;
    scanf("%d",&n);
	for(int i = 0; i < n; i++){
        scanf("%d%d",&point[i].x,&point[i].y);
    }
    mergeSort(point,0,n,0);
    // for(int i = 0; i < n; i++){
    //     printf("%d%d\n",point[i].x,point[i].y);
    // }
    printf("%lld\n",mergeSort(point,0,n,1));
    return 0;
} 

/*Input

3
2 2
4 3
5 1
Output

1*/

