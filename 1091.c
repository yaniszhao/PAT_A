#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXX 1286
#define MAXY 128
#define MAXZ 60
#define MAXDIR 6//方向个数

typedef struct {
    int x,y,z;
} Node;

//6个方向的增量矩阵
int X[MAXDIR]={1, -1, 0, 0, 0, 0};
int Y[MAXDIR]={0, 0, 1, -1, 0, 0};
int Z[MAXDIR]={0, 0, 0, 0, 1, -1};
int matrix[MAXX][MAXY][MAXZ];
int visit[MAXX][MAXY][MAXZ];
Node que[MAXX*MAXY*MAXZ];//用栈存会溢出，开小了又不够，只有开个全局了
int N,M,L,T;

int IsNodeOk(Node node)
{
    if (node.x<0||node.x>=N) return 0;
    if (node.y<0||node.y>=M) return 0;
    if (node.z<0||node.z>=L) return 0;
    return 1;
}

int bfs(Node node)
{
    int i, total=0;
    Node tmp;
    int head=0, tail=0;//que
    visit[node.x][node.y][node.z]=1;
    que[tail++]=node;
    while (head!=tail) {
        node=que[head++];
        total++;
        for (i=0; i<MAXDIR; i++) {
            tmp.x=node.x+X[i];
            tmp.y=node.y+Y[i];
            tmp.z=node.z+Z[i];
            //判断坐标的合法性要放在最前面，否则数组对应下标可能会越界
            if (IsNodeOk(tmp)&&!visit[tmp.x][tmp.y][tmp.z]&&matrix[tmp.x][tmp.y][tmp.z]) {
                visit[tmp.x][tmp.y][tmp.z]=1;
                que[tail++]=tmp;
            }
        }
    }
    return total<T?0:total;
}

void fun1()
{
    int i,j,k;
    Node node;
    int total=0;

    scanf("%d%d%d%d", &N, &M, &L, &T);
    for (k=0; k<L; k++)
        for (i=0; i<N; i++)
            for (j=0; j<M; j++)
                scanf("%d", &matrix[i][j][k]);

    for (k=0; k<L; k++)
        for (i=0; i<N; i++)
            for (j=0; j<M; j++)
                if (!visit[i][j][k]&&matrix[i][j][k]) {
                    node.x=i; node.y=j; node.z=k;
                    total+=bfs(node);
                }
    printf("%d", total);
}

//1、三维图的遍历，注意6个方向的增量矩阵和三维图的写法，dfs据说会超时，所以用bfs
//2、每一个联通分量内只会遍历一次，相当于计算联通分量内满足一定值的总合
//3、que开的太小了不够，太大了会栈溢出，求模重复用也不敢用因为不知道最大值取多少
//最好就是用全局变量了，如果这题全局超内存的话只有考虑cpp的queue了
int main(int argc, char *argv[])
{
   fun1();
}

