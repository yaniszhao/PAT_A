#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define INF 1e4

int CountCost(int cost[][MAX], int pre[], int s, int d)
{
    int num=0;
    while (pre[d]!=-1) {
        num+=cost[pre[d]][d];
        d=pre[d];
    }
    return num;
}

void dijk(int edge[][MAX], int cost[][MAX], int n, int dist[], int pre[], int s, int d)
{
    int i,j,min,minidx;
    int cost1, cost2;
    int visit[MAX]={0};
    
    for (i=0; i<n; i++) {
        dist[i]=INF;
        pre[i]=-1;
    }
    
    for (i=0; i<n; i++)
        if (edge[s][i]!=INF) {dist[i]=edge[s][i]; pre[i]=s;}
    
    dist[s]=0; pre[s]=-1;
    for (i=1; i<n; i++) {
        min=INF; minidx=0;
        for (j=0; j<n; j++)//找到最小值
            if (dist[j]<min && !visit[j]) {min=dist[j]; minidx=j;}
        visit[minidx]=1;
        
        for (j=0; j<n; j++) {//更新其他的
            if (!visit[j]) {
                if (dist[minidx]+edge[minidx][j]<dist[j]) {
                    dist[j]=dist[minidx]+edge[minidx][j];
                    pre[j]=minidx;
                }
                else if (dist[minidx]+edge[minidx][j]==dist[j]) {
                    cost1=CountCost(cost, pre, s, minidx)+cost[minidx][j];
                    cost2=CountCost(cost, pre, s, j);
                    if (cost1<cost2) pre[j]=minidx;
                }
            }
        }
    }
}

void fun1()
{
    int edge[MAX][MAX];
    int cost[MAX][MAX];
    int dist[MAX];
    int pre[MAX];
    int list[MAX], cnt=0;
    int n,m,s,d;
    int i,j,k;
    int dis,cos;

    scanf("%d%d%d%d", &n, &m, &s, &d);
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            edge[i][j]=cost[i][j]=INF;
    
    for (k=0; k<m; k++) {
        scanf("%d%d%d%d", &i, &j, &dis, &cos);
        edge[i][j]=edge[j][i]=dis;
        cost[i][j]=cost[j][i]=cos;
    }
    
    dijk(edge, cost, n, dist, pre, s, d);
    
    k=d;//本来用的d，但是最后还要用到，保存
    while (k!=-1) {list[cnt++]=k; k=pre[k];}
//    for (i=0; i<=(cnt-1)/2; i++) //reverse
//        {j=list[i]; list[i]=list[cnt-1-i]; list[cnt-1-i]=j;}
    
    for (i=cnt-1; i>=0; i--)//倒序输出就不用reverse了
        printf("%d ", list[i]);
    printf("%d %d", dist[d], CountCost(cost, pre, s, d));
}

//除了起始点，其他的每个点都是等价的，所以做一次dijk就可以了，不用记录多条路径再做dfs
int main(int argc, char *argv[])
{
    fun1();
}
