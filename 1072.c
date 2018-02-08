#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1011//下标从1开始
#define INF 10000//随便取得,差不多就行了

int e[MAX][MAX];
int dist[MAX];
float total[11]={0};
int n,m,k,d;

int GetPlaceId()
{
    char place[5], c;
    int i, id;

    for (i=0,c='a'; c!=' '; i++) {
        scanf("%c", &c);
        place[i]=(c==' '?0:c);
    }

    if (place[0]=='G') id=n+atoi(&place[1]);
    else id=atoi(place);
    return id;
}

void Dijk(int u)
{
    int visit[MAX];
    int i,j,min;
    memset(visit, 0, MAX*sizeof(visit[0]));
    for (i=1; i<=n+m; i++)//注意哪些地方要用n+m
        dist[i]=e[u][i];
    visit[u]=1;
    for (i=1; i<n+m; i++) {//不是<=,因为要少一次
        for (j=1, min=INF; j<=n+m; j++)//注意更新min
            if (dist[j]<min&&!visit[j]) {u=j; min=dist[u];}
        visit[u]=1;
        for (j=1; j<=n+m; j++)
            if (dist[u]+e[u][j]<dist[j])
                dist[j]=dist[u]+e[u][j];
    }
}

int IsAllHouseOk()
{
    int i;
    for (i=1; i<=n; i++)
        if (dist[i]>d) return 0;
    return 1;
}

float CountDist()
{
    int i;
    float sum=0;
    for (i=1; i<=n; i++)
        sum+=dist[i];
    return sum;
}

float GetMinDist()
{
    int i;
    float min=dist[1];
    for (i=2; i<=n; i++)
        if (dist[i]<min) min=dist[i];
    return min;
}

void fun1()
{
    char c;
    int i,j;
    int p1,p2,dis;
    int ans,min;
    float mindis;

    scanf("%d%d%d%d", &n,&m,&k,&d);
    for (i=1; i<=n+m; i++)//initialize
        for (j=1; j<=n+m; j++) e[i][j]=INF;

    for (i=0; i<k; i++) {
        p1=GetPlaceId();
        p2=GetPlaceId();
        scanf("%d%c", &dis, &c);
        e[p1][p2]=e[p2][p1]=dis;
    }

    min=0; total[0]=n*d+1; mindis=-1;
    for (i=1; i<=m; i++) {
        Dijk(n+i);
        ans=IsAllHouseOk();
        if (ans==0) continue;
        total[i]=CountDist();//ans?CountDist():0;
        dis=GetMinDist();
        if (dis>mindis) {min=i; mindis=dis;}
        else if (dis==mindis) {
            if (total[i]<total[min]) {min=i; mindis=dis;}
            //因为是从小到大的序号开始的，所以相等情况就没操作
        }
    }

    //注意小数点四舍五入的做法，只是简单的加0.05最后一个用例不过，比如1.146
    if (min==0) printf("No Solution");
    else printf("G%d\n%.1f %.1f", min, mindis, (int)((total[min]/n)*10.0+0.5)/10.0);
}

//1、比较条件有三个：
//第一条件：最小距离最大的优先，即要尽量远离居民
//第二条件：平均距离最短的优先
//第三条件：序号小的优先
//2、这道题还是比较繁琐的，既要处理名字，又要求最短路径，然后还要多重比较，最后小数点还要四舍五入
//3、四舍五入要处理好一点，不能只是简单的加0.05
int main(int argc, char *argv[])
{
   fun1();
}

