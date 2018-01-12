#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STAMAX 501//max num of stations
#define INF 1e7

typedef struct stPath {
    int arr[STAMAX];
    int len;
} Vect;

int edge[STAMAX][STAMAX];
int vert[STAMAX];
int visit[STAMAX]={0};
Vect stk;
Vect path;

int CountPathLen(Vect *path, int edge[][STAMAX])
{
    int i, sum=0;
    for (i=1; i<path->len; i++)
        sum+=edge[path->arr[i-1]][path->arr[i]];
    return sum;
}

void CountWeight(Vect *path, int cap, int *nsend, int *nback)
{
    int i,j;
    int back=0,send=0;
    cap=cap/2;
    for (i=1; i<path->len; i++) {
//        j=cap-(back+vert[path->arr[i]]);
//        if (j>0){
//            send+=j;
//            back=0;
//        }
//        else {
//            back=-j;
//        }
        if (vert[path->arr[i]]>cap) {
            back+=vert[path->arr[i]]-cap;
        }
        else {
            if (back+vert[path->arr[i]]>=cap) {
                back=back+vert[path->arr[i]]-cap;
            }
            else {
                send+=cap-(back+vert[path->arr[i]]);
                back=0;
            }
        }
    }
    if (nsend) *nsend=send;
    if (nback) *nback=back;
    return;;
    
}

void dfs(int idx, int dst, int n, int cap)
{
    int sum1,sum2,need1,need2,back1,back2;
    int i,j;
    visit[idx]=1;
    stk.arr[stk.len++]=idx;
    
    if (idx==dst) {
        sum1=CountPathLen(&path, edge);
        sum2=CountPathLen(&stk, edge);
        if (sum2<sum1)
            memcpy(&path, &stk, sizeof(path));
        else if (sum2==sum1) {
            CountWeight(&path, cap, &need1, &back1);
            CountWeight(&stk, cap, &need2, &back2);
            if (need2<need1||(need2==need1 && back2<back1)) {
                //当need相等时要比较back，否则有用例不过
                memcpy(&path, &stk, sizeof(path));
            }
        }
    }
    else {
        for (j=1; j<=n; j++) {
            if (edge[idx][j]!=INF && !visit[j])
                dfs(j, dst, n, cap);
        }
    }
    
    stk.len--;
    visit[idx]=0;
}

void fun1()
{//不能得满分，有几个用例过不了
    int cap,n,dst,m;
    int i,j,k,t;
    
    scanf("%d%d%d%d", &cap, &n, &dst, &m);

    for (i=0; i<=n; i++) {
        for (j=0; j<=n; j++) {
            //在这里全填INF也没有影响，方便后面判断
            //edge[i][j]=i==j?0:INF;
            edge[i][j]=INF;
        }
    }
    
    for (i=1; i<=n; i++)
        scanf("%d", &vert[i]);
    
    for (k=0; k<m; k++) {
        scanf("%d%d%d", &i, &j, &t);
        edge[i][j]=edge[j][i]=t;
    }
    
    stk.len=0;
    path.len=0;
        
    stk.arr[stk.len++]=0;
    path.arr[path.len++]=0;
    path.arr[path.len++]=dst;
    visit[0]=1;
    for (j=1; j<=n; j++) {
        if (edge[0][j]!=INF && !visit[i])
            dfs(j, dst, n, cap);
    }
    
    CountWeight(&path, cap, &k, &t);
    printf("%d %d", k, path.arr[0]);
    for (i=1; i<path.len; i++)
        printf("->%d", path.arr[i]);
    printf(" %d", t);

}

//=====================================================

Vect pre[STAMAX];
Vect minpath;
int dist[STAMAX];

void Dijk(int n)
{
    int u;
    int i,j;
    
    dist[0]=0;
    visit[0]=1;
    for (i=1; i<=n; i++) {
        u=-1;
        for (j=1; j<=n; j++) {
            if (!visit[j]) {
                if (u==-1) u=j;
                else if (dist[j]<dist[u]) u=j;
            }
        }
        visit[u]=1;
        
        for (j=1; j<=n; j++) {
            if (edge[u][j]!=INF && !visit[j]) {
                if (dist[u]+edge[u][j]<dist[j]) {
                    dist[j]=dist[u]+edge[u][j];
                    pre[j].arr[0]=u;
                    pre[j].len=1;
                }
                else if (dist[u]+edge[u][j]==dist[j]) {
                    pre[j].arr[pre[j].len++]=u;
                }
            }
        }
    }
}

void CountWeight2(Vect *path, int cap, int *nsend, int *nback)
{
    int i,j;
    int back=0,send=0;
    cap=cap/2;
    for (i=path->len-2; i>=0; i--) {
        if (vert[path->arr[i]]>cap) {
            back+=vert[path->arr[i]]-cap;
        }
        else {
            if (back+vert[path->arr[i]]>=cap) {
                back=back+vert[path->arr[i]]-cap;
            }
            else {
                send+=cap-(back+vert[path->arr[i]]);
                back=0;
            }
        }
    }
    if (nsend) *nsend=send;
    if (nback) *nback=back;
    return;;
    
}

void dfs2(int idx, int cap)
{
    int i,j;
    int need1, back1, need2, back2;
    static int pathnum=0;
    path.arr[path.len++]=idx;
    if (idx==0){
        if (pathnum==0) {//first
            memcpy(&minpath, &path, sizeof(path));
            pathnum++;
        }
        else {
            CountWeight2(&minpath, cap, &need1, &back1);
            CountWeight2(&path, cap, &need2, &back2);
            if (need2<need1||(need2==need1 && back2<back1)) {
                //当need相等时要比较back，否则有用例不过
                memcpy(&minpath, &path, sizeof(path));
            }
        }
    }
    else {
        for (i=0; i<pre[idx].len; i++)
            dfs2(pre[idx].arr[i], cap);
    }
    
    path.len--;
}

void fun2()
{//不能得满，最后两个用例过不了
    int cap,n,dst,m;
    int i,j,k,t;
    
    scanf("%d%d%d%d", &cap, &n, &dst, &m);
    
    for (i=0; i<=n; i++) {
        dist[i]=INF;
        pre[i].len=0;
        for (j=0; j<=n; j++) {
            //在这里全填INF也没有影响，方便后面判断
            //edge[i][j]=i==j?0:INF;
            edge[i][j]=INF;
        }
    }
    
    for (i=1; i<=n; i++)
        scanf("%d", &vert[i]);
    
    for (k=0; k<m; k++) {
        scanf("%d%d%d", &i, &j, &t);
        edge[i][j]=edge[j][i]=t;
        if (i==0) {
            dist[j]=t;
            pre[j].arr[pre[j].len++]=0;
        }
    }
    
    Dijk(n);
    path.len=0;
    dfs2(dst, cap);
    
    CountWeight2(&minpath, cap, &k, &t);
    printf("%d %d", k, 0);
    for (i=minpath.len-2; i>=0; i--)
        printf("->%d", minpath.arr[i]);
    printf(" %d", t);

}

int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}
