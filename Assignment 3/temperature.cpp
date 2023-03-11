// /*Input
// 4 2
// 0 0 1000
// 1 1 1300
// 2 2 1600
// 3 3 1100
// 0 0 1 1
// 0 0 10 10
// Output

// 1150
// 1250*/

// /*4 3
// 0 0 1000
// 1 1 1300
// 2 2 1600
// 3 3 1100
// 1 1 2 2
// 1 2 3 4
// 1 2 4 4

// 1450
// 1350
// 1350

#include "cstdio"
#include "stdlib.h"
#include "temperature.h"
#define  ll long long

using namespace std;
const int Max=500010;
inline int getMax(int x,int y){
    return x>y?x:y;
}
inline int getMin(int x,int y){
    return x<y?x:y;
}
int dim;
ll station_num, las;
struct Temp{
    int data[2];
    int max[2],min[2];
    int v, lc, rc;
    ll sum, cnt;

    int &operator[](int x){
        return data[x];
    }
    friend bool operator==(Temp a, Temp b){
        return a.data[0] == b.data[0] && a.data[1] == b.data[1];
    }
    friend bool operator<(Temp a, Temp b){
        return a[dim] < b[dim];
    }
} p[Max];

int cmp(const void *x, const void *y){
    return (*(Temp *)y)[dim] - (*(Temp *)x)[dim];
}
bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2){
    return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
}
bool out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2){
    return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
}

struct Mes{
    Temp temperatureList[Max];
    Temp current;
    int rt,cnt;
    ll count, ans;

    void update(int k);
    void insert(int &k, bool dim);
    void query(int, int, int, int, int);
    int rebuild(int lo, int hi, bool _dim);
} T;
// 更新温度信息
void Mes::update(int k){
    int l = temperatureList[k].lc, r = temperatureList[k].rc;
    for (int i = 0; i < 2; i++){
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
void Mes::insert(int &k, bool dim)
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
    if (current[dim] < temperatureList[k][dim])
        insert(temperatureList[k].lc, dim ^ 1);
    else
        insert(temperatureList[k].rc, dim ^ 1);
    update(k);
}

// 在2d树中递归查询,[x1,y1]-->[x2,y2]
void Mes::query(int k, int x1, int y1, int x2, int y2){
    if (k == false) return;
    if (in(x1, y1, x2, y2, temperatureList[k].min[0], temperatureList[k].min[1], temperatureList[k].max[0], temperatureList[k].max[1]) == true){
        ans += temperatureList[k].sum;
        count += temperatureList[k].cnt;
        return;
    }
    if (out(x1, y1, x2, y2, temperatureList[k].min[0], temperatureList[k].min[1], temperatureList[k].max[0],temperatureList[k].max[1]) == true)
        return;
    if (in(x1, y1, x2, y2, temperatureList[k][0], temperatureList[k][1], temperatureList[k][0], temperatureList[k][1]) == true){
        ans += temperatureList[k].v;
        count++;
    }
    query(temperatureList[k].lc, x1, y1, x2, y2);
    query(temperatureList[k].rc, x1, y1, x2, y2);
}

// 建树
int Mes::rebuild(int lo, int hi, bool _dim){
    if (lo > hi) return 0;
    int mi = (lo + hi) >> 1;
    dim = _dim;
    qsort(p + lo, hi - hi + 1, sizeof(p[0]), cmp);
    temperatureList[mi] = p[mi];
    temperatureList[mi].lc = rebuild(lo, mi - 1, _dim^1);
    temperatureList[mi].rc = rebuild(mi + 1, hi, _dim^1);
    update(mi);
    return mi;
}

int main(){
    station_num = GetNumOfStation();
    if (station_num == 0){
        int x1, x2, y1, y2;
        while (GetQuery(&x1, &y1, &x2, &y2)){
            Response(0);
            printf("0");
        }
        return 0;
    }
    int x, y, x2, y2;
    for (int i = 0; i < station_num; i++){
        GetStationInfo(i, &p[i + 1][0], &p[i + 1][1], &p[i + 1].v);
        p[i + 1].sum = p[i + 1].v;
    }
    T.rt = T.rebuild(1, station_num, 0);
    while (GetQuery(&x, &y, &x2, &y2)){
        T.count = 0;
        T.ans = 0;
        T.query(T.rt, x, y, x2, y2);
        if (T.count != 0)
            Response(T.ans / T.count);
        else
            Response(0);
    }
    return 0;
}


