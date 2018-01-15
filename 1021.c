#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 10001
#define INF 1e5

typedef struct stNode {
    int v;
    struct stNode *next;
} Node;

Node *edge[MAXLEN]={0};

int HaveEdge(int u, int v)
{
    Node *p;
    if (!edge[u] && !edge[v])
        return 0;

    p=edge[u];
    while (p) {
        if (p->v==v) return 1;
        p=p->next;
    }

    return 0;
}

void dfs(char visit[], int n, int root)
{
    Node *p=edge[root];
    visit[root]=1;
    while (p) {
        if (!visit[p->v])
            dfs(visit, n, p->v);
        p=p->next;
    }
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
    Node *p=edge[u];
    int d, maxd=0;
    visit[u]=1;

    while (p) {
        if (!visit[p->v]) {
            d=GetDeep(n, p->v);
            if (d>maxd) maxd=d;
        }
        p=p->next;
    }
    
    visit[u]=0;
    return maxd+1;
}

int GetDeep2(int n, int u)
{//bfs
    int visit[MAXLEN]={0};
    Node *p;
    int last, deep=0;
    int que[MAXLEN], head=0, tail=0;
    visit[u]=1;
    que[tail++]=u; last=u;
    
    while (head!=tail)
    {
        u=que[head++];
        p=edge[u];
        while (p) {
            if (!visit[p->v]) {
                visit[p->v]=1;
                que[tail++]=p->v;
            }
            p=p->next;
        }

        if (u==last) {
            deep++;
            last=que[tail-1];
        }
    }

    return deep;
}

//直接用数组会超内存,用char也超；动态数组会超内存；领接表会超时
//仿造stl的vector还是过了
void fun1()
{
    //int edge[MAXLEN][MAXLEN];//用数组存空间太大
    Node *p, *tmp;
    int deepest[MAXLEN], max=-1;
    int n;
    int i,j,cnt;
    scanf("%d", &n);

    while (scanf("%d %d", &i, &j)!=EOF) {
        if (edge[i]==NULL) {
            p=(Node *)malloc(sizeof(*p));
            p->v=j; p->next=NULL;
            edge[i]=p;
        }
        else {
            tmp=edge[i];
            while (tmp->next!=NULL) tmp=tmp->next;
            p=(Node *)malloc(sizeof(*p));
            p->v=j; p->next=NULL;
            tmp->next=p;
        }

        if (edge[j]==NULL) {
            p=(Node *)malloc(sizeof(*p));
            p->v=i; p->next=NULL;
            edge[j]=p;
        }
        else {
            tmp=edge[j];
            while (tmp->next!=NULL) tmp=tmp->next;
            p=(Node *)malloc(sizeof(*p));
            p->v=i; p->next=NULL;
            tmp->next=p;
        }
    }

    //如果成树，刚好边数是顶点个数减一,但数据不一定是树吧，最好不用这个
    //    for (i=0; i<n-1; i++) {
    //        scanf("%d %d", &i, &j);
    //        edge[i][j]=edge[j][i]=1;
    //    }

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
