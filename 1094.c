#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

int *edge[MAX]={NULL};
int cnt[MAX]={0};
int maxlev, maxnum=0;
int n,m;

void bfs(int u)
{
    int que[MAX], head=0, tail=0;
    int i, lev=1, num=0, last;

    que[tail++]=u;
    last=u;
    while (head!=tail) {
        u=que[head++];
        num++;
        if (cnt[u]>0)
            for (i=0; i<cnt[u]; i++)//是树不用visit[]
                que[tail++]=edge[u][i];

        if (last==u) {
            if (num>maxnum) {
                maxlev=lev;
                maxnum=num;
                num=0;
            }
            lev++;
            last=que[tail-1];
        }
    }
}

void fun1()
{
    int i, j, id;
    scanf("%d%d", &n, &m);
    for (i=0; i<m; i++) {
        scanf("%d", &id);
        scanf("%d", &cnt[id]);
        edge[id]=(int *)malloc(cnt[id]*sizeof(edge[0][0]));
        for (j=0; j<cnt[id]; j++)
            scanf("%d", &edge[id][j]);
    }
    bfs(1);
    printf("%d %d", maxnum, maxlev);
}

//1、树的bfs简单点；dfs也可以用个数组记录每层的个数,递归参数带入层数
//2、数据不大用邻接矩阵也可以，也可以用链表的邻接表；
//还可以直接用邻接矩阵的存储然后用我现在用的处理，只是我这里用的malloc
int main(int argc, char *argv[])
{
   fun1();
}

