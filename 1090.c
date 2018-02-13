#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000
typedef struct node {
    int chd;
    struct node *next;
} Node;

Node *edge[MAX]={NULL};
int cnt[MAX];
int n;
int maxdep=0, maxcnt=0;

void dfs(int u, int dep)
{
    Node *tmp;
    if (cnt[u]==0) {//零售商
        if (dep>maxdep) {
            maxdep=dep;
            maxcnt=1;
        }
        else if (dep==maxdep) {
            maxcnt++;
        }
    }
    else {
        for (tmp=edge[u]; tmp!=NULL; tmp=tmp->next)
            dfs(tmp->chd, dep+1);//树形不需要visit[]
    }
}

void fun1()
{
    int root;
    double p,r;
    int i,val;
    Node *tmp;
    scanf("%d%lf%lf", &n, &p, &r);
    for (i=0; i<n; i++) {
        scanf("%d", &val);
        if (val==-1) root=i;
        else {
            tmp=(Node *)malloc(sizeof(*tmp));
            tmp->chd=i;
            tmp->next=edge[val];
            edge[val]=tmp;//用头插法简单点
            cnt[val]++;
        }
    }
    dfs(root, 0);
    r=(r+100)/100.0;
    printf("%.2lf %d", p*pow(r,maxdep), maxcnt);
}

//和1079类似的题，根据之前的教训，直接用double类型，且不用四舍五入
//dfs和bfs都可以，因为bfs代码简单所以用dfs
//用邻接矩阵内存果然超限了，之前担心这个所以用的cpp
//用c写的动态邻接表还是不怎么麻烦，1079也可以参考这个来完成
int main(int argc, char *argv[])
{
   fun1();
}

