#include <stdio.h>
#include "temperature.h"

typedef struct _station_type
{
    int x, y;
    int temp;
} station_type;

static FILE * fr = NULL;
static FILE * fw = NULL;

static int n, m;
static int last_response, query_index;
static station_type stations[50000];

// 该函数必须首先调用，返回现有观察站的总数n。
extern int GetNumOfStation(void)
{
    int i;
    fr = fopen("temperature.in", "r");
    fw = fopen("temperature.out", "w");
    fscanf(fr, "%d %d", &n, &m);
    for (i = 0; i < n; i++)
      fscanf(fr, "%d %d %d", &stations[i].x, &stations[i].y, 
                  &stations[i].temp);
    query_index = 0;
    last_response = 0;
    return n;
}

// 获得第no个（0 ≤ no < n）观察站的信息：其地理坐标(*x,*y)及其所测温度值*temp。各观测站的测量精度统一以0.01℃为基准单位，比如12.34℃表示为整数1234。
extern void GetStationInfo(int no, int *x, int *y, int *temp)
{
    *x = stations[no].x;
    *y = stations[no].y;
    *temp = stations[no].temp;
}

// 接收下一查询请求。返回值1对应于一次有效的查询。矩阵区域的四边分别与x或y轴平行，
// (*x1,*y1)和(*x2,*y2)分别为其西南角和东北角的坐标。恰好被矩形边界穿过的观察站，也视作落在其中。若返回0，则表示没有更多的查询，你的程序可以退出。
extern int GetQuery(int *x1, int *y1, int *x2, int *y2)
{
    if (query_index < m) {
        fscanf(fr, "%d %d %d %d", x1, y1, x2, y2);
        query_index++;
        return 1;
    } else
      return 0;
}

// 针对当前的查询，在计算出对应的平均气温后，你可通过这一接口报告所得数值(截断取整，比如12.345℃输出为1234，-12.345℃输出为-1234)。
extern void Response(int temp)
{
    if (last_response > query_index)
      fprintf(fw, "No Query\n");
    for (last_response++; last_response < query_index; last_response++)
      fprintf(fw, "Missing\n");
    fprintf(fw, "%d\n", temp);
    if (query_index == m) {
        fclose(fr);
        fclose(fw);
    }
}
