#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAX 10
void fun1()
{
    int a,b,len;
    char s[MAX];
    cin>>a>>b;
    a+=b;
    if (a<0) {cout<<'-'; a=-a;}
    snprintf(s, MAX, "%d", a);
    len=strlen(s); b=len%3; len-=b;//处理了第一组，后面就全是3个的
    for (int i=0; i<b; i++) cout<<s[i];
    if (b>0 && len>0) cout<<',';//注意len>0的条件
    for (int i=0; i<len; i++) {//处理后面3个3个的
        cout<<s[b+i];
        if (i!=len-1 && (i+1)%3==0) cout<<',';//最后一个不能打印
    }
}

void fun2()
{
    int a,b,len;
    char s[MAX];
    cin>>a>>b;
    a+=b;
    if (a<0) {cout<<'-'; a=-a;}
    snprintf(s, MAX, "%d", a);
    len=strlen(s);
    for (int i=0; i<len; i++) {//一次打印，剩下的是3的倍数，当前点就要打印逗号
        cout<<s[i];
        if (i<len-1 && (len-i-1)%3==0) cout<<',';//最后一个不能打印
    }
}

int main(int argc, char *argv[])
{
    fun2();
}
