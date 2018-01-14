#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
using namespace std;

#define MAXLEN 10001
#define INF 1e5

vector<int> edge[MAXLEN];

void dfs(char visit[], int n, int root)
{
    int i;
    visit[root]=1;
    for (i=0; i<edge[root].size(); i++)
        if (!visit[edge[root][i]])
            dfs(visit, n, edge[root][i]);
}

int CountComponent(int n)
{
    char visit[MAXLEN];
    int i, cnt=0;
    memset(visit, 0, MAXLEN);
    for (i=1; i<=n; i++) {
        if (!visit[i]) {
            cnt++;
            dfs(visit, n, i);
        }
    }
    return cnt;
}

int GetDeep(int n, int u)
{//递归
    static char visit[MAXLEN]={0};
    int i, d, maxd=0;
    visit[u]=1;
    for (i=0; i<edge[u].size(); i++) {
        if (!visit[edge[u][i]]) {
            d=GetDeep(n, edge[u][i]);
            if (d>maxd) maxd=d;
        }
    }
    visit[u]=0;
    return maxd+1;
}

int GetDeep2(int n, int u)
{//bfs
    int visit[MAXLEN]={0};
    int i, last, deep=0;
    int que[MAXLEN], head=0, tail=0;
    visit[u]=1;
    que[tail++]=u; last=u;
    while (head!=tail)
    {
        u=que[head++];
        
        for (i=0; i<edge[u].size(); i++) {
            if (!visit[edge[u][i]]) {
                visit[edge[u][i]]=1;
                que[tail++]=edge[u][i];
            }
        }
        
        if (u==last) {
            deep++;
            last=que[tail-1];
        }
    }
    
    return deep;
}

//直接用数组会超内存,用char也超；动态数组会超内存；领接表会超时
//只有用vector破了
void fun1()
{
    //int edge[MAXLEN][MAXLEN];//用数组存空间太大
    int deepest[MAXLEN], max=-1;
    int n;
    int i,j,cnt;
    scanf("%d", &n);
    
    //这个scanf在mac上调试会超时，不知道为什么
    while (scanf("%d %d", &i, &j)!=EOF) {
        edge[i].push_back(j);
        edge[j].push_back(i);
    }
    
    cnt=CountComponent(n);
    if (cnt>1) {
        printf("Error: %d components", cnt);
    }
    else {
        for (i=1; i<=n; i++) {
            j=GetDeep2(n, i);
            if (j>max) {
                max=j; cnt=1;
                deepest[cnt-1]=i;
            }
            else if (j==max) {
                cnt++;
                deepest[cnt-1]=i;
            }
        }
        for (i=0; i<cnt; i++) {
            printf("%d\n", deepest[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    fun1();
}


