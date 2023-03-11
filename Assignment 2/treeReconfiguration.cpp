#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include<malloc.h>
using namespace std;

const int MAX = 4000050;
int preOrder[MAX];
int postOrder[MAX];

struct BinNode{ 
   int data; 
   BinNode* ltree;
   BinNode* rtree;               
};

BinNode* recon(int preStart, int preEnd, int postStart, int postEnd)
{
	int len;
	int findL;

    BinNode* P = (BinNode*)malloc(sizeof(BinNode));
    P->data = preOrder[preStart]; // preOrder[preStart] == P
    P->rtree = NULL;
	P->ltree = NULL;

    if (postStart == postEnd)
        return P;

    for (int i = postStart; i <= postEnd; i++)
    {
        if (postOrder[i]==preOrder[preStart + 1]) // preOrder[preStart + 1] == L
        {
            findL = i; // findL 查找的是后序遍历中，L所在的位置
            break;
        } 
    }
    len = findL-postStart+1; // 对应的是左子树对应序列的长度,也就是左子树元素个数
    P->ltree = recon(preStart+1, preStart+len, postStart, findL);
    P->rtree = recon(preStart+len+1, preEnd, findL+1, postEnd-1);
	// 观察发现前序遍历序列为$PL...R...$，而后序遍历序列为$...L...RP$
    return P;
}

void visit(int xdata){
	printf("%d ",xdata);
}

void travIn_R (BinNode* x) 
{
	if(x==NULL) return;
	travIn_R(x->ltree);
	visit(x->data);
	travIn_R(x->rtree);
};


int main(){
    int n;
	scanf("%d",&n);
	for (int i=0; i<n; i++){
		scanf("%d",&preOrder[i]);
	}
	for (int i=0; i<n; i++){
		scanf("%d",&postOrder[i]);
	}
    BinNode* root = recon(0, n-1, 0, n-1);
    travIn_R(root);
    return 0;
}

/*
Input
5
1 2 4 5 3
4 5 2 3 1
Output
4 2 5 1 3

input：
13
1 2 4 8 9 5 3 6 7 10 12 13 11
8 9 4 5 2 6 12 13 10 11 7 3 1
output：
8 4 9 2 5 1 6 3 12 10 13 7 11
*/

/*
PPT code
p: 当前重构子树根节点
pre0: 当前处理的前缀序列的起始位置 pre1: 当前处理的前缀序列终止位置 
in0: 当前处理的中缀序列的起始位置 in1: 当前处理的中缀序列的终止位置
void Recon(BinNode* p, int pre0, int pre1, int in0, int in1){
  设置当前子树根节点的值 p->data = PreSeq [pre0];
  确定中序序列根节点位置 int root_in = find(InSeq,p->data); 
  计算左右子树节点数目 int nL, nR;
  左子树的前序序列起始位置 int preL0 = pre0 + 1;
  左子树的前序序列终止位置 int preL1 = preL0+nL-1;
  左子树的中序序列起始位置 int inL0 = in0;
  左子树的前序序列终止位置 int inL1 = in0+nL-1;
  同样计算右子树的preR0,preR1,inR0,inR1;
  if (nL>0) { //递归调用
	产生新的左根节点pL; Recon(pL,preL0,preL1,inL0,inL1);}
  if (nR>0) {//递归调用
       产生新的左根节点pR; Recon(pR,preR0,preR1,inR0,inR1);}

*/