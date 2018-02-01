#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int wei[MAX]={0};
int e[MAX][MAX]={0}, vnum[MAX]={0};
int result[MAX][MAX+1]={0}, cnt=0;//多加一个字符存-1，表结尾
int stk[MAX];
int n,m,s;

void  dfs(int u, int level)
{
    int i,sum=0;
    
    stk[level-1]=u;
    if (vnum[u]==0) {//是叶子结点
        for (i=0; i<level; i++)
            sum+=wei[stk[i]];
        if (sum==s) {
            for (i=0; i<level; i++)
                result[cnt][i]=wei[stk[i]];
            result[cnt][level]=-1;//作结尾
            cnt++;
        }
    }
    else {
        for (i=0; i<vnum[u]; i++)
            dfs(e[u][i], level+1);
    }
}

int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    int i;
    for (i=0; x[i]!=-1&&y[i]!=-1; i++)
        if (x[i]>y[i]) return 1;
    return 0;
}

void fun1()
{
    int i,j,k,t;
    scanf("%d%d%d", &n, &m, &s);
    for (i=0; i<n; i++) scanf("%d", &wei[i]);
    for (k=0; k<m; k++) {
        scanf("%d%d", &i, &t);
        vnum[i]=t;
        while (t--) {
            scanf("%d", &j);
            e[i][t]=j;
        }
    }
    
    dfs(0, 1);
    qsort(result, cnt, sizeof(result[0]), cmp);
    for (i=cnt-1; i>=0; i--) {//排序按大到小排有问题，就小大排，逆序输出
        printf("%d", result[i][0]);
        for (j=1; result[i][j]!=-1; j++)
            printf(" %d", result[i][j]);
        putchar(10);
    }
}

//=====================================================
void  dfs2(int u, int level, int sum)
{//加个了sum的变量，省去循环求sum值
    int i;
    stk[level-1]=u;
    sum+=wei[u];
    if (vnum[u]==0) {//是叶子结点
        if (sum==s) {
            for (i=0; i<level; i++)
                result[cnt][i]=wei[stk[i]];
            result[cnt][level]=-1;//作结尾
            cnt++;
        }
    }
    else {
        for (i=0; i<vnum[u]; i++)
            dfs2(e[u][i], level+1, sum);
    }
}

int cmp2(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return wei[*y]-wei[*x];//按权值排序
}

void fun2()
{
    int i,j,k,t;
    scanf("%d%d%d", &n, &m, &s);
    for (i=0; i<n; i++) scanf("%d", &wei[i]);
    for (k=0; k<m; k++) {
        scanf("%d%d", &i, &t);
        vnum[i]=t;
        while (t--) {
            scanf("%d", &j);
            e[i][t]=j;
        }
        //先按权值从大到小排好序
        qsort(e[i], vnum[i], sizeof(e[0][0]), cmp2);
    }
    
    dfs2(0, 1, 0);
    for (i=0; i<cnt; i++) {//排序按大到小排有问题，就小大排，逆序输出
        printf("%d", result[i][0]);
        for (j=1; result[i][j]!=-1; j++)
            printf(" %d", result[i][j]);
        putchar(10);
    }
}

//fun1有个用例不过，应该是排序的问题
//fun2根据权值先拍好序，后面就可以不用排序，直接输出就是期望的结果
//bfs可以带个sum的参数，每次只需要加上自己本身就可以了，就不用循环求sum了
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}

