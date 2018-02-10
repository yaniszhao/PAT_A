#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

#define MAX 100000

vector<int> vertex[MAX];
int sale[MAX];//大于0为零售商且为销售量
int visit[MAX];//其实是树要不要visit都无所谓了
int n;
double p,r;
double total=0;

void dfs(int u, int dep)
{
    int i;
    if (u>=n) return;
    visit[u]=1;
    if (vertex[u].size()==0)
        total+=sale[u]*p*pow((r+100)/100, dep);
    else {
        for (i=0; i<vertex[u].size(); i++)
            if (!visit[vertex[u][i]]) {
                dfs(vertex[u][i], dep+1);
            }
    }
}

void bfs()
{
    int que[MAX], head, tail;
    int i, u, dep, last;
    head=tail=0;
    que[tail++]=0;
    last=0; dep=0;
    while (head!=tail) {
        u=que[head++];
        if (vertex[u].size()==0) {
            total+=sale[u]*p*pow((r+100)/100, dep);
        }
        else {
            for (i=0; i<vertex[u].size(); i++)
                que[tail++]=vertex[u][i];
        }

        if (u==last) {
            dep++;
            last=que[tail-1];
        }
    }
}

void fun1()
{
    int i,j,num,chd;
    scanf("%d%lf%lf", &n, &p, &r);
    for (i=0; i<n; i++) {
        scanf("%d", &num);
        if (num==0) {//零售商
            scanf("%d", &sale[i]);
            continue;
        }
        for (j=0; j<num; j++) {//供应商
            scanf("%d", &chd);
            vertex[i].push_back(chd);
        }
    }
    //dfs(0, 0);
    bfs();
    printf("%.1lf", total);
}

//用一维数组存父亲的结点号，简单的用bfs或dfs都要超时
//即使把每个结点的层记录下来，答案也是错误
//存成邻接矩阵的话太浪费空间了，存成邻接表c语言又不方便
//存成邻接表用cpp的vector做好一点,bfs和dfs都过了
//不把类型设成double过不了，有关钱的还是设成double吧，小数点不用四舍五入
int main(int argc, char *argv[])
{
   fun1();
}

