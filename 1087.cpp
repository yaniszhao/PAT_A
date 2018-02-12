#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;

#define MAX 200
#define INF 0x7FFFFFFF//这里小了一个用例不过

int edge[MAX][MAX];
int wei[MAX];
int n,k;
vector<int> path, spath;
int cntpath, minval=INF, maxhap;
int visit[MAX]={0};
int st, ed;

void dfs(int u, int sumpath, int sumhap)
{
    path.push_back(u);
    visit[u]=1;

    if (u==ed) {
        if (sumpath<minval) {
            spath.assign(path.begin(), path.end());
            minval=sumpath;
            maxhap=sumhap;
            cntpath=1;
        }
        else if (sumpath==minval) {
            cntpath++;
            if (sumhap>maxhap) {
                spath.assign(path.begin(), path.end());
                minval=sumpath;
                maxhap=sumhap;
            }
            else if (sumhap==maxhap&&path.size()<spath.size()) {
                spath.assign(path.begin(), path.end());
                minval=sumpath;
                maxhap=sumhap;
            }
        }
    }
    else {
        for (int i=0; i<n; i++)
            if (edge[u][i]>0&&!visit[i])
                dfs(i, sumpath+edge[u][i], sumhap+wei[i]);
    }

    path.pop_back();
    visit[u]=0;
}

void fun1()
{
    map<string, int>::iterator it;
    map<string, int> map;
    string start, end, tmps1, tmps2;
    int i, val, u, v;
    cin>>n>>k>>start; end="ROM";
    map[start]=0;
    for (i=1; i<n; i++) {
        cin>>tmps1>>val;
        map[tmps1]=i;
        wei[i]=val;
    }
    for (i=0; i<k; i++) {
        cin>>tmps1>>tmps2>>val;
        u=map[tmps1]; v=map[tmps2];
        edge[u][v]=edge[v][u]=val;
    }
    st=map[start]; ed=map[end];
    dfs(st, 0, 0);
    cout<<cntpath<<" "<<minval<<" "<<maxhap<<" "<<maxhap/(spath.size()-1)<<endl;
    cout<<start;
    for (i=1; i<spath.size(); i++) {
        for (it=map.begin(); it->second!=spath[i]; it++);
        cout<<"->"<<it->first;
    }
}

//不想用c写，INF定义小了会有一个用例不过，好奇怪，之前有到类似的题不过不知道是不是这个原因
//只用了dfs不过加了两个数字存路径
//后面有空用c写下
int main1(int argc, char *argv[])
{
    fun1();
}
