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
#define ll long long
const int MAX_n = 4000010;
const int MAX_m = 2000010;

struct Task{
    ll priority;
    char name[10];
    Task makeTask(ll _priority, char _name[10]){
        Task task;
        task.priority=_priority;
        strcpy(task.name,_name);
        return task;
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

int numCounts = 0;
Task heapDataVec[MAX_n];

// make heap
struct MyHeap{
    void makeHeap(int n);
    void insert(Task task);
    void percolateUp(int index, Task value);
    void delMin();
    void percolateDown(int childTree, Task value);
    void push_back(Task task);
};

void swap(Task *a,Task *b){
   Task temp=*a;
   *a=*b;
   *b=temp;
}

void MyHeap::push_back(Task task){
    heapDataVec[numCounts] = task;
}

void MyHeap::insert(Task task){
    push_back(task);
    cout<<"insert: "<<task.priority<<" "<<task.name<<endl;
    ++numCounts;
    percolateUp(numCounts-1, heapDataVec[numCounts-1]);
}

void MyHeap::percolateUp(int index, Task value){
    int parentIndex = (index - 1) / 2;
    while (index > 0 && (value < heapDataVec[parentIndex])){ //改为小于，维护最小值
        heapDataVec[index] = heapDataVec[parentIndex];
        index = parentIndex;
        parentIndex = (parentIndex -1) / 2;
    }
    heapDataVec[index] = value;
    cout<<"Min: "<<heapDataVec[0].priority<<" "<<heapDataVec[0].name<<endl;
}

// delmin
void MyHeap::delMin(){
    Task value = heapDataVec[numCounts-1];
    cout<<"delMin: "<<value.priority<<" "<<value.name<<endl;
    heapDataVec[numCounts-1] = heapDataVec[0];
    //堆中元素数目减一  
    --numCounts;
    percolateDown (0, value);  // 下滤
}

void MyHeap::percolateDown(int childTree, Task value){
    int index = childTree;                               // 目标节点索引  
    ll minChid = 2*(index + 1) ;                        // 目标节点右子节点
    bool godown = true;                                      // 循环下滤退出标志
    while (godown && numCounts < minChid) {
        godown = false;
        if (heapDataVec[minChid-1] < heapDataVec[minChid]) 
             --minChid;                                      //若左孩子小，则更新为左孩子 
        if (heapDataVec[minChid] < value) {            //若父节点大于孩子，则下滤 
            godown = true;
            heapDataVec[index] = heapDataVec[minChid];   //令较大值为交换值 
            index = minChid;                             //该交换节点索引下移  
            minChid = 2 * (minChid + 1);                     //重新计算交换节点右子节点  
        }
    }
    if (minChid == numCounts){
        if(heapDataVec[minChid - 1] < value){          //令左子节点值为交换值
            heapDataVec[index] = heapDataVec[minChid - 1];
            index = minChid - 1;
        }
    }
    heapDataVec[index] = value;                    //将调整值赋予交换节点
}

// void MyHeap::makeHeap(int n){
//     //建堆的过程就是一个不断调整堆的过程，循环调用函数percolateDown调整子树  
//     this->numCounts = n;
//     if (numCounts < 2) return;
//     //第一个需要调整的子树的根节点地址
//     int parent = (numCounts)/2 -1;
//     while (1){
//         percolateDown(parent, heapDataVec[parent]);
//         if (0 == parent) return; // 到达根节点，返回
//         --parent;
//    }
// }

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
    MyHeap heap;
    // heap.makeHeap(n);
	for (int i=0;i<n;i++){
		int _priority; char _name[10];
		scanf("%d%s",&_priority, _name);
        Task obj;
        obj.priority=_priority;
        strcpy(obj.name,_name);
		heap.insert(obj);
	}
    
	for (int i=0; i<m; i++){
        heap.delMin();
    }
	return 0;
}

// int main()
// {
//     int n,m;
//     scanf("%d%d", &n, &m);
//     for (int i = 1; i <= n; i++)
//         scanf("%lld%s", &task[i].v, task[i].word);
//     heapify();

//     for (int i = 0; n && i < m; i++)
//     {
//         printf("%s\n", task[1].word);
//         task[1].v *= 2;
//         if (task[1].v >= INF)
//             task[1] = task[n--];
//         percolateDown(1);
//     }

//     return 0;
// }

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
5 5
1 1
3 3
2 2
5 5
4 4
*/

