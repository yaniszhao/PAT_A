#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 500
#define INF 1e7

int visit[MAX];
int wei[MAX];
int maxwei[MAX];
int e[MAX][MAX];
int dist[MAX];
int num[MAX];
int n,m,c1,c2;

void Dijk()
{
    int u, min;
    int i,j;

    fill(begin(dist), end(dist), INF);
    dist[c1]=0;
    num[c1]=1;
    maxwei[c1]=wei[c1];

    for (j=0; j<n; j++) {
        min=INF;
        for (i=0; i<n; i++)//找到剩下最小的一个结点
            if (!visit[i] && dist[i]<min)
                {u=i; min=dist[i];}

        visit[u]=1;
        if (min==INF) break;//剩下的都不可达
        if (u==c2) break;//后面的都大于或等于c2的长度没意义

        for (i=0; i<n; i++) {//更新后面的结点
            if (visit[i] || e[u][i]==0) continue;

            if (dist[u]+e[u][i]<dist[i]) {
                dist[i]=dist[u]+e[u][i];
                num[i]=num[u];//不是1
                maxwei[i]=maxwei[u]+wei[i];
            }
            else if (dist[u]+e[u][i]==dist[i]) {
                num[i]=num[u]+num[i];//不是num[i]+1
                if (maxwei[u]+wei[i]>maxwei[i])
                    maxwei[i]=maxwei[u]+wei[i];
            }
        }
    }
}

void fun1()
{
    int i,j,val;
    cin>>n>>m>>c1>>c2;
    for (i=0; i<n; i++) cin>>wei[i];
    for (int k=0; k<m; k++) {
        cin>>i>>j>>val;
        e[i][j]=e[j][i]=val;
    }
    Dijk();
    //cout<<dist[c2]<<' '<<maxwei[c2];//计算个数不是最短距离
    cout<<num[c2]<<' '<<maxwei[c2];
}
//===================================================================

int mindis=INF;
int num_c2;
int maxw;

void dfs(int u, int dis, int w)
{
    if (u==c2) {
        if (dis<mindis) {
            mindis=dis;
            num_c2=1;
            maxw=w;
        }
        else if (dis==mindis) {
            num_c2++;
            maxw=w>maxw?w:maxw;
        }
        return;
    }

    visit[u]=1;
    for (int i=0; i<n; i++) {
        if (visit[i] || e[u][i]==0) continue;
        dfs(i, dis+e[u][i], w+wei[i]);
    }
    visit[u]=0;
}

void fun2()
{
    int i,j,val;
    cin>>n>>m>>c1>>c2;
    for (i=0; i<n; i++) cin>>wei[i];
    for (int k=0; k<m; k++) {
        cin>>i>>j>>val;
        e[i][j]=e[j][i]=val;
    }
    dfs(c1, 0, wei[c1]);
    cout<<num_c2<<' '<<maxw;
}

//1、这题完全不用cpp就可以做，因为顶点的个数并不多直接用邻接矩阵就可以了
//2、fun1用的Dijk算法，注意更新个数num[i]的赋值关系
//3、fun2用的dfs算法，时间可能会长点，但是这题数据不大比较适合
int main(int argc, char *argv[])
{
    fun1();
}
