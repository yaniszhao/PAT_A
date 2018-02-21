#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

enum enType {TITLE=1,AUTHOR,KEY,PUBLISHER,YEAR};

void fun1()
{
    map<string, set<int> > map[6];
    int n,m;
    string str;
    int i,id,type,cnt;

    cin>>n;
    for (i=0; i<n; i++) {
        scanf("%d\n", &id);
        getline(cin, str);
        map[TITLE][str].insert(id);
        getline(cin, str);
        map[AUTHOR][str].insert(id);
        while (cin>>str) {
            map[KEY][str].insert(id);
            char c=getchar();
            if (c=='\n') break;
        }
        getline(cin, str);
        map[PUBLISHER][str].insert(id);
        getline(cin, str);
        map[YEAR][str].insert(id);
    }

    cin>>m;
    for (i=0; i<m; i++) {
        scanf("%d: ", &type);//这里用scanf吸收": "
        getline(cin, str);
        cout<<type<<": "<<str<<endl;
        cnt=0;
        for (auto it : map[type][str]) {
            printf("%07d\n", it);
            cnt++;
        }
        if (cnt==0) printf("Not Found\n");
    }
}

//1、用C写了一堆还有两个用例不知道怎么过不了
//2、用map和set写起来就很方便了，速度也不比C写的慢
//3、auto这种语法糖也还是好用啊
int main(int argc, char *argv[])
{
    fun1();
}
