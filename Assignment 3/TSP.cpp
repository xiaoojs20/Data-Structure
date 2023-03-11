#include<cstdio>

const int MAX_n=1000010;
const int MAX_m=1000010;
int inDegree[MAX_n]={0};
int tpSorted[MAX_n];

int Max(int x, int y){
    return x>y? x:y;
}
   
struct Node{
    int item;
    Node *next;
    Node(int _item, Node *_next=NULL){
        item = _item;
        next = _next;
    }
};

struct Link{
    Node* _next;
    int linkLen;
    Link():_next(NULL), linkLen(1){}
    void addEdge(int next_id);
}Link[MAX_n];


void Link::addEdge(int next_id){
    ++inDegree[next_id];
    if(!_next){
        _next = new Node(next_id);
    }
    else{
        _next = new Node(next_id, _next);
    }
}
// n starts from 1;
int topological_sort(int n){
    int maxLen = 0;
    int tpSize = 0;
    // 将所有入度为0的顶点入队
    for(int i = 1; i <= n; i++)
        if(!inDegree[i])
            tpSorted[tpSize++] = i;
    
    // 对数组进行操作
    // 将所有v指向的顶点的入度减1，并将入度减为0的顶点入栈
    // 更新最长距离
    for(int i = 0; i < tpSize; i++){
        Node* cur = Link[tpSorted[i]]._next;
        while(cur){
            Link[cur->item].linkLen = Max(Link[tpSorted[i]].linkLen+1, Link[cur->item].linkLen);
            maxLen = Max(Link[cur->item].linkLen, maxLen);
            inDegree[cur->item]--;
            if(!inDegree[cur->item])
                tpSorted[tpSize++] = cur->item;
            cur = cur->next;
        }
    }
    return maxLen;
}

int main(){
    int n, m;
    int start, end;
    scanf("%d%d",&n,&m);
    for(int i=0; i<m; i++){
        scanf("%d%d",&start,&end);
        Link[start].addEdge(end);  
    }
	printf("%d\n",topological_sort(n));
	return 0;
}


/*Input

4 3
1 4
2 4
4 3

Output
3*/