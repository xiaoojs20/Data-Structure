#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;

const int MAX_n=10011,MAX_m=30011;
int first[MAX_n];
int visited[MAX_n];
int num=2;

struct Edge{
    int v;
    int u;
};

// 插入一次存两遍
Edge edges[MAX_m*2];

void add_xy(int x,int y){
    Edge &e=edges[num];
    e.v=y;
    e.u=first[x];
    first[x]=num++;
}

// 记录两点连通，扩充连通分量
void insert(int x,int y){
    add_xy(x,y);
    add_xy(y,x);
}


int paint(int x,int col)
{
	visited[x]=col;
	for (int i=first[x];i;i=edges[i].u)
	{
		int &u=edges[i].v;
		if (visited[u] && visited[u]==col) return 0;
		if (!visited[u] && !paint(u,col^1)) return 0;
	}
	return 1;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		insert(x,y);
	}
	// memset(vis,0,sizeof(vis));
	for (int x=1;x<=n;x++)
        if (!visited[x])
		    if (paint(x,2)==0) {
                printf("-1");
                return 0;
            }
	printf("1");
	return 0;
}


// /*输入样例
// 4 3
// 1 2
// 1 3
// 2 4
// 输出样例
// 1*/

// /*输入样例
// 4 3
// 1 2
// 1 3
// 2 3
// 输出样例
// -1*/
