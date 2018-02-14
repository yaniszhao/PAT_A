#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>

using namespace std;

#define MAX 100000
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
    queue<Node> que;//que的大小不能太大了
    Node tmp;
    visit[node.x][node.y][node.z]=1;
    que.push(node);
    while (!que.empty()) {
        node=que.front(); que.pop();
        total++;
        for (i=0; i<MAXDIR; i++) {
            tmp.x=node.x+X[i];
            tmp.y=node.y+Y[i];
            tmp.z=node.z+Z[i];
            //判断坐标的合法性要放在最前面，否则数组对应下标可能会越界
            if (IsNodeOk(tmp)&&!visit[tmp.x][tmp.y][tmp.z]&&matrix[tmp.x][tmp.y][tmp.z]) {
                visit[tmp.x][tmp.y][tmp.z]=1;
                que.push(tmp);
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

int main(int argc, char *argv[])
{
   fun1();
}

