#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX 101

char *map[]={"zero", "one", "two", "three", "four", \
        "five", "six", "seven", "eight", "nine"};
        
void fun1()
{
    string s;
    int sum=0;
    cin>>s;
    for (auto it : s) sum+=it-'0';
    s=to_string(sum);
    if (s.size()>0) cout<<map[s[0]-'0'];
    for (auto it=s.begin()+1; it!=s.end(); it++)
        cout<<' '<<map[*it-'0'];
}

//fun1:先求和然后转出字符串，在打印每一个字节对应的英文字符。
int main(int argc, char *argv[])
{
    fun1();
}
