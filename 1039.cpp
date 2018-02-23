#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define MAX 26*26*26*10
#define MAXTIMESTR 5
#define CharToInt(c, x) ((c-'A')*x)

int NameToInt(char name[5])
{
    int sum=0;
    sum+=CharToInt(name[0], 26*26*10);
    sum+=CharToInt(name[1], 26*10);
    sum+=CharToInt(name[2], 10);
    sum+=name[3]-'0';
    return sum;
}

void fun1()
{//简单，但是最后一个用例会超时
    map<string, set<int> > map;
    int n,k;
    int i, j, id, num;
    string name;
    cin>>n>>k;
    for (i=0; i<k; i++) {
        cin>>id>>num;
        for (j=0; j<num; j++) {
            cin>>name; getchar();
            map[name].insert(id);
        }
    }

    for (i=0; i<n; i++) {
        cin>>name; getchar();
        cout<<name<<" "<<map[name].size();
        for (auto it : map[name]) cout<<" "<<it;
        cout<<endl;
    }
}

set<int> mmap[MAX];//放里面栈大小不够会段错误
void fun2()
{
    int n,k;
    int i, j, pos, id, num;
    char name[5], c;
    cin>>n>>k;
    for (i=0; i<k; i++) {
        scanf("%d%d\n", &id, &num);
        for (j=0; j<num; j++) {
            scanf("%s%c", name, &c);
            pos=NameToInt(name);
            mmap[pos].insert(id);
        }
    }

    for (i=0; i<n; i++) {
        scanf("%s%c", name, &c);
        pos=NameToInt(name);
        printf("%s %d", name, mmap[pos].size());
        for (auto it : mmap[pos]) printf(" %d", it);
        putchar('\n');
    }
}

//1、fun1用map加string加set很快就做出来了，但是会超时；因为有string/cin/cout
//2、fun2把名字hash之后用set也挺快，但是hash空间要放在全局区; 避免使用string/cin/cout
int main(int argc, char *argv[])
{
    fun2();
}
