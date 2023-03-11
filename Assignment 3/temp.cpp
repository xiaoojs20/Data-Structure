#include "cstdio"
#include "stdlib.h"
#include "temperature.h"

using namespace std;

long long int val1, val2, las;

struct Node1
{
    int data[2];
    int max[2];
    int min[2];
    int v, l, r;
    long long int sum, cnt;

    int &operator[](int x)
    {
        return data[x];
    }

    friend bool operator==(Node1 a, Node1 b)
    {
        return a.data[0] == b.data[0] && a.data[1] == b.data[1];
    }

    friend bool operator<(Node1 a, Node1 b)
    {
        return a[val2] < b[val2];
    }
} p[200005];

struct Node2
{
    Node1 temperatureList[200005];
    Node1 current;
    int rt;
    int cnt;
    long long int count, ans;

    void NodeUpdate(int);
    void NodeUpdate(int &, bool);
    void NodeUpdate(int, int, int, int, int);
    int NodeUpdate(int, int, bool);
} T;

int CMP(const void *, const void *);
bool Insert(int, int, int, int, int, int, int, int);
bool Outter(int, int, int, int, int, int, int, int);
inline int getMax(int, int);
inline int getMin(int, int);

int main()
{
    val1 = GetNumOfStation();
    if (val1 == 0)
    {
        int x1, x2, y1, y2;
        while (GetQuery(&x1, &y1, &x2, &y2))
        {
            Response(0);
            printf("0\val1");
        }
        return 0;
    }
    int x, y, x2, y2;
    for (int i = 0; i < val1; i++)
    {
        GetStationInfo(i, &p[i + 1][0], &p[i + 1][1], &p[i + 1].v);
        p[i + 1].sum = p[i + 1].v;
    }
    T.rt = T.NodeUpdate(1, val1, 0);
    while (GetQuery(&x, &y, &x2, &y2))
    {
        T.count = 0;
        T.ans = 0;
        T.NodeUpdate(T.rt, x, y, x2, y2);

        if (T.count != 0)
        {
            Response(T.ans / T.count);
        }
        else
        {
            Response(0);
        }
    }
    return 0;
}

int CMP(const void *x, const void *y)
{
    return (*(Node1 *)y)[val2] - (*(Node1 *)x)[val2];
}
bool Insert(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
}
bool Outter(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2)
{
    return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
}
inline int getMax(int a, int b)
{
    return (a > b ? a : b);
}
inline int getMin(int a, int b)
{
    return (a < b ? a : b);
}

void Node2::NodeUpdate(int k)
{
    int l = temperatureList[k].l, r = temperatureList[k].r;
    for (int i = 0; i < 2; i++)
    {
        temperatureList[k].min[i] = temperatureList[k].max[i] = temperatureList[k][i];
        if (l)
            temperatureList[k].min[i] = getMin(temperatureList[k].min[i], temperatureList[l].min[i]);
        if (l)
            temperatureList[k].max[i] = getMax(temperatureList[k].max[i], temperatureList[l].max[i]);
        if (r)
            temperatureList[k].min[i] = getMin(temperatureList[k].min[i], temperatureList[r].min[i]);
        if (r)
            temperatureList[k].max[i] = getMax(temperatureList[k].max[i], temperatureList[r].max[i]);
    }
    temperatureList[k].sum = temperatureList[k].v + temperatureList[l].sum + temperatureList[r].sum;
    temperatureList[k].cnt = 1 + temperatureList[l].cnt + temperatureList[r].cnt;
}
void Node2::NodeUpdate(int &k, bool val2)
{
    if (!k)
    {
        k = ++cnt;
        temperatureList[k][0] = temperatureList[k].min[0] = temperatureList[k].max[0] = current[0];
        temperatureList[k][1] = temperatureList[k].min[1] = temperatureList[k].max[1] = current[1];
    }
    if (current == temperatureList[k])
    {
        temperatureList[k].v += current.v, temperatureList[k].sum += current.v;
        return;
    }
    if (current[val2] < temperatureList[k][val2])
        NodeUpdate(temperatureList[k].l, val2 ^ 1);
    else
        NodeUpdate(temperatureList[k].r, val2 ^ 1);
    NodeUpdate(k);
}
void Node2::NodeUpdate(int k, int x1, int y1, int x2, int y2)
{
    if (k == false)
    {
        return;
    }
    if (Insert(x1, y1, x2, y2, temperatureList[k].min[0], temperatureList[k].min[1], temperatureList[k].max[0], temperatureList[k].max[1]) == true)
    {
        ans += temperatureList[k].sum;
        count += temperatureList[k].cnt;
        return;
    }
    if (Outter(x1, y1, x2, y2, temperatureList[k].min[0], temperatureList[k].min[1], temperatureList[k].max[0],
               temperatureList[k].max[1]) == true)
    {
        return;
    }
    if (Insert(x1, y1, x2, y2, temperatureList[k][0], temperatureList[k][1], temperatureList[k][0], temperatureList[k][1]) == true)
    {
        ans += temperatureList[k].v;
        count++;
    }
    NodeUpdate(temperatureList[k].l, x1, y1, x2, y2);
    NodeUpdate(temperatureList[k].r, x1, y1, x2, y2);
}
int Node2::NodeUpdate(int l, int r, bool f)
{
    if (l > r)
    {
        return 0;
    }
    int temp = (l + r) >> 1;
    val2 = f;
    qsort(p + l, r - l + 1, sizeof(p[0]), CMP);
    temperatureList[temp] = p[temp];
    temperatureList[temp].l = NodeUpdate(l, temp - 1, f ^ 1);
    temperatureList[temp].r = NodeUpdate(temp + 1, r, f ^ 1);
    NodeUpdate(temp);
    return temp;
}
