#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000

int tree[MAX];
int cnt[MAX];
int sale[MAX];//-1为供应商，0为分销商，大于0为零售商且为销售量
int visit[MAX];//其实要不要visit都无所谓了
int n;
double p,r;
double total=0;

void dfs(int u, int dep)
{//一般操作的dfs要超时
    int i,count=0;
    if (u>=n) return;
    visit[u]=1;
    if (cnt[u]==0)
        total+=sale[u]*p*pow((r+100)/100, dep);
    else {
        for (i=1; i<n&&count<cnt[u]; i++)
            if (tree[i]==u&&!visit[i]) {
                count++;//为了提前退出
                dfs(i, dep+1);
            }
    }
}

void bfs()
{//一般操作的bfs也要超时
    int que[MAX], head, tail;
    int i, u, dep, last;
    head=tail=0;
    que[tail++]=0;
    last=0; dep=0;
    while (head!=tail) {
        u=que[head++];
        if (cnt[u]==0) {
            total+=sale[u]*p*pow((r+100)/100, dep);
        }
        else {
            for (i=1; i<n; i++)
                if (tree[i]==u) que[tail++]=i;
        }

        if (u==last) {
            dep++;
            last=que[tail-1];
        }
    }
}

int level[MAX];
void Count()
{
    int i,u,lev;
    for (i=1; i<n; i++) {
        for (u=i, lev=0; u!=0; u=tree[u]) {
            lev++;
            if (level[tree[u]]!=0) {//做了这个处理才不会超时
                lev=level[tree[u]]+lev;
                break;
            }
        }
        level[i]=lev;
    }
    for (u=1; u<n; u++) {
        if (cnt[u]==0)
            total+=sale[u]*p*pow((r+100)/100, level[u]);
    }
}

void fun1()
{
    int i,j,num,chd;
    scanf("%d%lf%lf", &n, &p, &r);
    for (i=0; i<n; i++) {
        scanf("%d", &num);
        cnt[i]=num;
        if (num==0) {//零售商
            scanf("%d", &sale[i]);
            continue;
        }
        for (j=0; j<num; j++) {//供应商
            scanf("%d", &chd);
            tree[chd]=i;
        }
    }
    //dfs(0, 0);
    //bfs();
    Count();
    printf("%.1lf", total);
}

//用一维数组存父亲的结点号，简单的用bfs或dfs都要超时
//即使把每个结点的层记录下来，答案也是错误--是因为没改成double，改了只有1分得不到
//存成邻接矩阵的话太浪费空间了，存成邻接表c语言又不方便
//存成邻接表用cpp的vector做好一点,bfs和dfs都过了
//不把类型设成double过不了，有关钱的还是设成double吧，小数点不用四舍五入
//只有改成邻接表来做了，其实也复杂不了多少
int main(int argc, char *argv[])
{
   fun1();
}

