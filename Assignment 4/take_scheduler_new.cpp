#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
/*二叉堆
插入即上滤，删除置换下，构建自底下，排序始构建，迭代做删除。
0 <= n <= 4,000,000
0 <= m <= 2,000,000
0 < Initial priority number < 2^32
*/

// #define uint unsigned int
#define ll long long
const int MAX_n = 4000010;
const int MAX_m = 2000010;

struct Task{
    ll priority;
    char name[10];
	Task() {}
	Task(ll _priority,char* _name): priority(_priority){
		memcpy(name,_name,strlen(_name)+1);
	}
    friend bool operator==(Task a, Task b){
        return a.priority == b.priority && strcmp(a.name,b.name) == 0;
    }
    friend bool operator<(Task a, Task b){
        if(a.priority < b.priority) return true;
        else if(a.priority == b.priority && strcmp(a.name,b.name) < 0) return true;
        else return false;
    }
};

struct MyHeap{
	Task tasks[MAX_n]; int size;
	MyHeap() {size=0;}
	void swap(int x, int y);
	void insert(ll val,char *name);
	void percolateUp(int x);
	void delMin();
	void percolateDown(int x);
	void top();
}heap;

void MyHeap::swap(int x, int y){
	Task tmp(tasks[x]);
	tasks[x]=tasks[y];
	tasks[y]=tmp;
}
void MyHeap::percolateUp(int x){
	if (x==1) return;
	int parent=x>>1;
	if (tasks[parent]<tasks[x]) return;
	swap(parent,x);
	percolateUp(parent);
}

void MyHeap::insert(ll val,char *name){
	tasks[++size]=Task(val,name);
	percolateUp(size);
}

void MyHeap::percolateDown(int x){
	int lc=x<<1,rc=(x<<1)|1;
	if (rc<=size && tasks[rc]<tasks[x]){
		if (tasks[rc]<tasks[lc]){
			swap(x,rc);
			percolateDown(rc);
		}
		else{
			swap(x,lc);
			percolateDown(lc);
		}
	}
	else if(lc<=size && tasks[lc]<tasks[x]){
		swap(x,lc);
		percolateDown(lc);
	}
}

void MyHeap::delMin(){
	// 堆顶和size处置换，删除size处(Min)，下滤
	swap(size,1);
	size--;
	percolateDown(1);
}
void MyHeap::top(){
	if (size==0) return;
	puts(tasks[1].name);
	if (((tasks[1].priority>>31)&1)==0){
		tasks[1].priority<<=1;
		percolateDown(1);
	}
	else delMin(); 
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		ll _priority; char _name[10];
		scanf("%lld%s",&_priority,_name);
		heap.insert(_priority,_name);
	}
	for (int i=0;i<m;i++)
		heap.top();
	return 0;
}

/*Input

3 3
1 hello
10 test
2 world

Output

hello
hello
world*/

/*
3 9
1 hello
10 test
2 world
*/