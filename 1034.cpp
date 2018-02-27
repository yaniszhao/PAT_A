#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define MAX (26*26*26)

typedef struct {
    string head;
    int num;
} Gangs;

map<string, int> mmap;
int edge[MAX][MAX];
vector<Gangs> gangs;
int wei[MAX];
int visit[MAX];
int head, total;

int GetId(string name)
{
    int id;
    if (mmap.find(name)!=mmap.end())
        return mmap[name];
    id=mmap.size();
    mmap[name]=id;
    return id;
}

string GetName(int n)
{
    for (auto it : mmap)
        if (it.second==n)
            return it.first;
    return NULL;
}

int dfs(int u)
{
    int i, num=1;

    visit[u]=1;
    total+=wei[u];
    if (wei[u]>wei[head]) head=u;

    for (i=0; i<mmap.size(); i++)
        if (edge[u][i]>0 && visit[i]==0)
            num+=dfs(i);
    return num;
}

bool cmp(Gangs a, Gangs b)
{
    return a.head<b.head;
}

void fun1()
{
    int n,k;
    int i,time,id1,id2,num;
    string name1,name2;
    Gangs tmp;

    cin>>n>>k;
    for (i=0; i<n; i++) {
        cin>>name1>>name2>>time;
        id1=GetId(name1);
        id2=GetId(name2);
        edge[id1][id2]+=time;
        edge[id2][id1]+=time;
        wei[id1]+=time;
        wei[id2]+=time;
    }

    for (i=0; i<mmap.size(); i++) {
        if (visit[i]==0) {
            head=i;
            total=0;
            num=dfs(i);
            if (num>2 && total>k*2) {
                tmp.head=GetName(head);
                tmp.num=num;
                gangs.push_back(tmp);
            }
        }
    }

    sort(gangs.begin(), gangs.end(), cmp);
    cout<<gangs.size()<<endl;
    for (auto it : gangs)
        cout<<it.head<<' '<<it.num<<endl;
}
//==============================================
typedef struct {
    int head;
    int num;
} Gangs2;

vector<int> e[MAX];
vector<Gangs2> gangs2;
int NameToInt(char name[])
{
    int sum=0;
    sum+=(name[0]-'A')*26*26;
    sum+=(name[1]-'A')*26;
    sum+=(name[2]-'A');
    return sum;
}

void IntToName(char name[4], int n)
{
    name[0]=n/(26*26)+'A'; n%=(26*26);
    name[1]=n/26+'A'; n%=26;
    name[2]=n+'A';
    name[3]=0;
}

int dfs2(int u)
{
    int i, num=1;

    visit[u]=1;
    total+=wei[u];
    if (wei[u]>wei[head]) head=u;

    for (i=0; i<e[u].size(); i++)
        if (visit[e[u][i]]==0)
            num+=dfs2(e[u][i]);
    return num;
}

bool cmp2(Gangs2 a, Gangs2 b)
{
    return a.head<b.head;
}

void fun2()
{
    int n,k;
    int i,time,id1,id2,num;
    char name1[4],name2[4];
    Gangs2 tmp;

    cin>>n>>k;
    for (i=0; i<n; i++) {
        scanf("%s%s%d", name1, name2, &time);
        id1=NameToInt(name1);
        id2=NameToInt(name2);
        e[id1].push_back(id2);
        e[id2].push_back(id1);
        wei[id1]+=time;
        wei[id2]+=time;
    }

    for (i=0; i<MAX; i++) {
        if (visit[i]==0) {
            head=i;
            total=0;
            num=dfs2(i);
            if (num>2 && total>k*2) {
                tmp.head=head;
                tmp.num=num;
                gangs2.push_back(tmp);
            }
        }
    }

    sort(gangs2.begin(), gangs2.end(), cmp2);
    cout<<gangs2.size()<<endl;
    for (auto it : gangs2) {
        IntToName(name1, it.head);
        printf("%s %d\n", name1, it.num);
    }
}

//1、输入的数据是有向的，要把数据整合成无向的
//2、直接用邻接矩阵循环的时候太费时间了而且很多位置应该都是空的，通过map映射之后的要好点
//3、计算联通图内的总权值用边计算不好计算，最好是通过点，然后除以2
//4、用点来计算总权值，则用邻接表也好做了
int main(int argc, char *argv[])
{
    fun2();
}
