#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX 26//(26*26*26)
#define MAX 2000
#define INF 1e7

//#define NameToInt(name) (name[0]-'A')//((name[2]-'A')*26*26+(name[1]-'A')*26+name[0]-'A')
//void IntToName (char name[], int v)
//{
//    name[3]='\0';
//    name[2]=v%26+'A';
//    v=v/26;
//    name[1]=v%26+'A';
//    v=v/26;
//    name[0]=v+'A';
//}

//用于字符串转下标
char map[MAX][4];
int cnt=0;

int NameToInt(char name[])
{
    int i;
    for (i=0; i<cnt; i++)
        if (strcmp(map[i], name)==0)
            return i;
    return -1;
}

void IntToName(char name[], int v)
{
    memcpy(name, map[v], 4);
}

float CountWei(int e[][MAX], int u)
{
    float wei=0;
    int i;
    for (i=0; i<cnt; i++)
        if (e[u][i]!=INF) wei+=e[u][i];
    return wei/2;
}

//return返回成员数,head返回带头大哥,wei返回下面所有结点的权值和
void  dfs(int e[][MAX], int visit[], int vwei[], int u, int *head, int *totalwei, int *members)
{
    int i;
    
    visit[u]=1;
    (*totalwei)+=vwei[u];
    (*members)++;
    if (vwei[u]>vwei[*head]) *head=u;
    
    for (i=0; i<cnt; i++)
        if (!visit[i] && e[u][i]!=INF)
            dfs(e, visit, vwei, i, head, totalwei, members);
    return;
}

typedef struct stNode {
    int gang;
    int members;
} Node;

int cmp(const void *a, const void *b)
{
    return ((Node*)a)->gang>((Node*)a)->gang;
}

void fun1()
{
    
    int (*edge)[MAX];
    int vwei[MAX]={0};//vertex weight
    int visit[MAX]={0};
    int n,k;
    char name1[4],name2[4];
    int n1,n2;
    int i,j,val;
    int gang, members, totalwei;
    Node que[MAX], tmpnode;
    int head=0, tail=0;
    
    scanf("%d%d", &n, &k);
    //map=(char (*)[4])malloc(MAX*4);
    edge=(int (*)[MAX])malloc(2*n*MAX*sizeof(int));//要用2n，因为可能每行的两个都不同
    for (i=0; i<n; i++) for (j=0; j<=i; j++) edge[i][j]=edge[j][i]=INF;
    
    for (i=0; i<n; i++) {
        scanf("%s %s %d", name1, name2, &val);
        n1=NameToInt(name1);
        if (n1==-1) {memcpy(map[cnt++], name1, 4); n1=cnt-1;}
        n2=NameToInt(name2);
        if (n2==-1) {memcpy(map[cnt++], name2, 4); n2=cnt-1;}
        vwei[n1]+=val; vwei[n2]+=val;
        if (edge[n1][n2]==INF) {
            edge[n1][n2]=edge[n2][n1]=val;
        }
        else {
            val+=edge[n1][n2];
            edge[n1][n2]=edge[n2][n1]=val;
        }
        
    }
    
    for (i=0; i<cnt; i++) {
        if (!visit[i]) {
            totalwei=0; members=0; gang=i;
            dfs(edge, visit, vwei, i, &gang, &totalwei, &members);
            if (members>2 && totalwei>k*2) {
                tmpnode.gang=gang;
                tmpnode.members=members;
                que[tail++]=tmpnode;
            }
        }
    }
    qsort(que, tail, sizeof(que[0]), cmp);
    printf("%d\n", tail);
    for (head=0; head<tail; head++) {
        IntToName(name1, que[head].gang);
        printf("%s %d\n", name1, que[head].members);
    }
}


int main(int argc, char *argv[])
{
    fun1();
}
