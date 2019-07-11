#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX 100
#define INF 1e7

vector<int> e[MAX];
int cnt[MAX];//dfs
int maxlev=0;//dfs

void bfs()
{
    int u=1, last=1, cnt=0;
    queue<int> que;
    que.push(u);
    while (!que.empty()) {
        u=que.front(); que.pop();
        if (e[u].size()==0) cnt++;
        else for (auto it : e[u]) que.push(it);
        if (u==last) {
            if (u!=1) cout<<' ';
            cout<<cnt;
            cnt=0;
            last=que.back();
        }
    }
}


void dfs_rec(int u, int lev)
{
    if (lev>maxlev) maxlev=lev;
    if (e[u].size()==0) cnt[lev]++;
    else for(auto it : e[u]) dfs_rec(it, lev+1);
}

void dfs()
{
    dfs_rec(1, 0);
    cout<<cnt[0];
    for (int i=1; i<=maxlev; i++)
        cout<<' '<<cnt[i];
}

void fun1()
{
    int n,m;
    cin>>n>>m;
    for (int i=0; i<m; i++) {
        int id1,id2,num;
        cin>>id1>>num;
        for (int j=0; j<num; j++) {
            cin>>id2;
            e[id1].push_back(id2);
        }
    }
    //bfs();
    dfs();
}

//1、树可以用图的dfs和bfs都可以做，即fun1
//2、构造成链树(孩子兄弟法)，然后树的递归遍历，其实和dfs原理是一样的，参考c代码
//3、用双亲表示法来做,用一个数据结构来存父亲结点和是否有孩子，一次遍历可以得到，
//至于层数的获取要用递归到根结点才能得到
int main(int argc, char *argv[])
{
    fun1();
}
