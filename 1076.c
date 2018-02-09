#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1001
#define INF 10000

int e[MAX][MAX];
int visit[MAX];
int N,L,K;

int dfs(int u, int dep)
{
    int i,cnt=0;
    if (dep>L) return 0;
    visit[u]=1;
    if (dep==L) return 1;//剪枝
    for (i=1; i<MAX; i++)
        if (!visit[i]&&e[i][u])
            cnt+=dfs(i, dep+1);
    return dep>0?cnt+1:cnt;
}

void dfs2(int u, int dep)
{
    int i;
    if (dep>L) return;
    visit[u]=1;
    if (dep==L) return;//剪枝
    for (i=1; i<MAX; i++)
        if (e[i][u])
            dfs(i, dep+1);
    return;
}

int CountVisit()
{
    int i, cnt=0;
    for (i=1; i<MAX; i++)
        if (visit[i]) cnt++;
    return cnt;
}

int bfs(int u)
{
    int que[MAX], head, tail;
    int last, dep=0;
    int i, cnt=0;
    head=tail=0;
    que[tail++]=last=u;
    visit[u]=1;
    while (head!=tail) {
        u=que[head++];
        if (dep==L) continue;//return cnt;
        //没到最大层就继续入列
        for (i=1; i<MAX; i++) {
            if (!visit[i]&&e[i][u]) {
                que[tail++]=i;
                visit[i]=1;
                cnt++;
            }
        }
        //一层已经完了，更新
        if (last==u) {
            dep++;
            last=que[tail-1];
        }
    }
    return cnt;
}

//用dfs有个问题，比如L是2，路径可以是1->2->3->4，也可以是1->3->4
//而且只有3能到4，那么走一条路径4就不会被访问到，走第二条就可以访问；
//要解决它两种方法：
//1、即使访问过的结点还是去访问，总有一次是以最小的去访问的，但空间大而且有回路应该有问题
//2、层序或者Dijk确定一个点的最小高度，那还不然直接用bfs
//用方法1解决后还是用例不过，应该是解决方法本来就不可靠，有空验证下方法2是否可行
void fun1()
{
    int i,j;
    int num, id;
    scanf("%d%d", &N, &L);
    memset(e, 0, MAX*MAX*sizeof(e[0][0]));
    for (i=1; i<=N; i++) {
        scanf("%d", &num);
        for (j=0; j<num; j++) {
            scanf("%d", &id);
            e[i][id]=1;
        }
    }
    scanf("%d", &K);
    for (i=0; i<K; i++) {
        memset(visit, 0, MAX*sizeof(visit[0]));
        scanf("%d", &id);
        printf("%d\n", bfs(id));
        //下面是dfs
//        printf("%d\n", dfs(id, 0));
//        dfs2(id, 0);
//        printf("%d\n", CountVisit()-1);
    }
}

//这道题不能用bfs会有问题，见上面的分析；是否能得出带有最大深度的题最好别用bfs？
//用bfs比较简单；也可以用Dijk求最短路径，然后求最短路径小于L的点有多少个
int main(int argc, char *argv[])
{
   fun1();
}

