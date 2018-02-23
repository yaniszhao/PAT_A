#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;

#define MAX 81

void fun1()
{
    char map[128]={0};
    string s1, s2;
    char c;
    cin>>s1>>s2;
    for (auto &it: s1) if (isalpha(it)) it=toupper(it);
    for (auto &it: s2) if (isalpha(it)) it=toupper(it);
    for (auto it : s1)
        if (s2.find(it)==string::npos && map[it]==0) {
            cout<<it;
            map[it]=1;
        }
}

void fun2()
{
    string s1, s2, ans;
    cin>>s1>>s2;
    for (auto &it: s1) if (isalpha(it)) it=toupper(it);
    for (auto &it: s2) if (isalpha(it)) it=toupper(it);
    for (auto it : s1)
        if (s2.find(it)==string::npos && ans.find(it)==string::npos)
            ans.push_back(it);
    cout<<ans;
}

//选把字符转换成大写，然后通过寻找字符串来做
int main(int argc, char *argv[])
{
    fun2();
}
