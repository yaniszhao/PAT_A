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
int edge2[MAXLEN]={0};

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

#define HaveEdge2(u, v) (edge2[v])

void RefleshEdge(int u)
{
    Node *p;
    memset(edge, 0, MAXLEN*sizeof(*edge));
    p=edge[u];
    while (p) {
        edge2[p->v]=1;
        p=p->next;
    }
}

void dfs(char visit[], int n, int root)
{
    int i;
    visit[root]=1;
    for (i=1; i<=n; i++)
        if (!visit[i] && HaveEdge2(root, i))
            dfs(visit, n, i);
}

int CountComponent(int n)
{
    char visit[MAXLEN];
    int i, cnt=0;
    memset(visit, 0, MAXLEN);
    for (i=1; i<=n; i++) {
        if (!visit[i]) {
            RefleshEdge(i);
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
    for (i=1; i<=n; i++) {
        if (!visit[i] && HaveEdge2(u, i)) {
            d=GetDeep(n, i);
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

        for (i=1; i<=n; i++) {
            if (!visit[i] && HaveEdge2(u, i)) {
                visit[i]=1;
                que[tail++]=i;
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
