#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAX 1001//从1开始

vector<int> e[MAX];
int visit[MAX];
int n,m,k;

void dfs(int u)
{
    visit[u]=1;
    for (auto it : e[u])
        if (!visit[it]) dfs(it);
}

void bfs(int u)
{//没有求层数，代码还是比较简单了
    queue<int> que;
    que.push(u);
    visit[u]=1;
    while(!que.empty()) {
        u=que.front(); que.pop();
        for (auto it : e[u])
            if (!visit[it]) {
                que.push(it);
                visit[it]=1;
            }
    }
}

void fun1()
{
    cin>>n>>m>>k;
    for (int i=0; i<m; i++) {
        int id1,id2;
        cin>>id1>>id2;
        e[id1].push_back(id2);
        e[id2].push_back(id1);
    }
    for (int i=0; i<k; i++) {
        int u,cnt=0;
        cin>>u;
        //memset(visit, 0, MAX*sizeof(visit[0]));
        fill(begin(visit), end(visit), 0);
        visit[u]=1;//去掉损失结点
        for (int i=1; i<=n; i++)//计算联通分量个数
            if (!visit[i]) {
                cnt++;
                dfs(i);
                //bfs(i);
            }
        cout<<cnt-1<<endl;
    }
}

//1、用邻接表做节约空间
//2、损失结点不用拷贝e然后去掉相邻边，只需要把visit置1访问就会绕过它
//3、dfs和bfs都可以，dfs代码简单
//4、最后一个用例都快超时了，想必是cin和cout效率要差一些的原因
//5、还可以用并查集来做
int main(int argc, char *argv[])
{
    fun1();
}
