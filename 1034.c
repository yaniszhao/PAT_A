#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (26*26*26)

typedef struct {
    int gang;
    int members;
} Gang;

//用于字符串转下标
char map[MAX][4];
int cnt=0;
int edge[MAX][MAX];
int vwei[MAX]={0};//vertex weight
int visit[MAX]={0};
int gang, totalwei;

void IntToName (char name[], int v)
{
    name[0]=v/(26*26)+'A'; v%=(26*26);
    name[1]=v/26+'A'; v%=26;
    name[2]=v+'A';
    name[3]='\0';
}

int NameToInt(char name[])
{
    int sum=0;
    sum+=(name[0]-'A')*26*26;
    sum+=(name[1]-'A')*26;
    sum+=(name[2]-'A');
    return sum;
}

int dfs(int u)
{
    int i, num=1;
    visit[u]=1;
    totalwei+=vwei[u];
    if (vwei[u]>vwei[gang]) gang=u;
    for (i=0; i<MAX; i++)
        if (!visit[i] && edge[u][i]>0)
            num+=dfs(i);
    return num;
}

int cmp(const void *a, const void *b)
{
    return ((Gang*)a)->gang>((Gang*)a)->gang;
}

void fun1()
{//全部超时
    int n,k;
    char name1[4],name2[4];
    int n1,n2;
    int i,val,num;
    Gang que[MAX], tmp;
    int head=0, tail=0;

    scanf("%d%d", &n, &k);
    for (i=0; i<n; i++) {
        scanf("%s %s %d", name1, name2, &val);
        n1=NameToInt(name1);
        n2=NameToInt(name2);
        vwei[n1]+=val;
        vwei[n2]+=val;
        edge[n1][n2]+=val;
        edge[n2][n1]+=val;
    }

    for (i=0; i<MAX; i++) {
        if (!visit[i]) {
            gang=i;
            totalwei=0;
            num=dfs(i);
            if (num>2 && totalwei>k*2) {
                tmp.gang=gang;
                tmp.members=num;
                que[tail++]=tmp;
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
//===================================================

int NameToInt2(char name[4])
{
    int i;
    for (i=0; i<cnt; i++)
        if (strcmp(map[i], name)==0)
            return i;
    //如果没找到重新插入
    memcpy(map[cnt++], name, sizeof(map[0]));
    return cnt-1;
}

char *IntToName2(int n)
{
    return map[n];
}

int dfs2(int u)
{
    int i, num=1;
    visit[u]=1;
    totalwei+=vwei[u];
    if (vwei[u]>vwei[gang]) gang=u;
    for (i=0; i<cnt; i++)
        if (!visit[i] && edge[u][i]>0)
            num+=dfs2(i);
    return num;
}

int cmp2(const void *a, const void *b)
{//根据字符大小排序
    char *name1, *name2;
    Gang *x=(Gang *)a;
    Gang *y=(Gang *)b;
    name1=IntToName2(x->gang);
    name2=IntToName2(y->gang);
    return strcmp(name1, name2);
}

void fun2()
{
    int n,k;
    char name1[4],name2[4];
    int n1,n2;
    int i,val,num;
    Gang que[MAX], tmp;
    int head=0, tail=0;

    scanf("%d%d", &n, &k);
    for (i=0; i<n; i++) {
        scanf("%s %s %d", name1, name2, &val);
        n1=NameToInt2(name1);
        n2=NameToInt2(name2);
        vwei[n1]+=val;
        vwei[n2]+=val;
        edge[n1][n2]+=val;
        edge[n2][n1]+=val;
    }

    for (i=0; i<cnt; i++) {
        if (!visit[i]) {
            gang=i;
            totalwei=0;
            num=dfs(i);
            if (num>2 && totalwei>k*2) {
                tmp.gang=gang;
                tmp.members=num;
                que[tail++]=tmp;
            }
        }
    }

    qsort(que, tail, sizeof(que[0]), cmp2);
    printf("%d\n", tail);
    for (head=0; head<tail; head++)
        printf("%s %d\n", IntToName2(que[head].gang), que[head].members);
}

int main(int argc, char *argv[])
{
    fun2();
}
