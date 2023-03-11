#include<cstdio>
#include<iostream>
using namespace std;

const int MAX = 10010;
char balls[MAX]; // balls: A or B or C
int numA, numB, numC;
int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",balls);
    numA=numB=numC=0;
    for(int i=0; i<n; i++){
        if(balls[i]=='A') numA++;
        else if(balls[i]=='B') numB++;
        else numC++;

        if(numA+numC<numB){
            printf("False");
            return 0;
        }
    }
    numA=numB=numC=0;
    for(int i=n-1; i>=0; i--){
        if(balls[i]=='A') numA++;
        else if(balls[i]=='B') numB++;
        else numC++;

        if(numA>numB+numC){
            printf("False");
            return 0;
        }     
    }
    printf("True");
    return 0;
}


/*
输入样例
3
ABC
输出样例
True

ACBBCA => AABBBA: False
AAABBC => AAABBB: True
CABACABAC => ABABABAB: True
CABBCAAAC => ABBBAAAB: False
*/
