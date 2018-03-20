#include <iostream>
#include <algorithm>
#include <strstream>
#include <iomanip>
#include <vector>
using namespace std;
#define LLONG_MAX 0x7FFFFFFFFFFFFFFF
typedef long long LLONG;

int map[128];

LLONG Transform(string s, LLONG radix)
{
    LLONG n=0;
    for (int i=0; i<s.size(); i++)
        n=n*radix+map[s[i]];
    return n;
}

LLONG Judge(LLONG n1, string s2)
{
    int max=0;
    LLONG low, high, mid, n2;
    for (auto it : s2) if (map[it]>max) max=map[it];
    low=max+1;
    high=n1;//最大n1就够了，不要取LLONG_MAX
    while (low<=high) {
        mid=(low+high)/2;
        //mid=low+(high-low)/2;//不限定high上面表达式会溢出
        n2=Transform(s2, mid);
        if (n2<0) {high=mid-1; continue;}//n2溢出则减小radix
        if (n1>n2) low=mid+1;
        else high=mid-1;
    }
    if (n1==Transform(s2, low)) return low;
    else return 0;
}

void fun1()
{
    string s1,s2;
    LLONG n1,tag,radix;
    cin>>s1>>s2>>tag>>radix;
    if (tag==2) swap(s1,s2);
    for (char i='0'; i<='9'; i++) map[i]=i-'0';
    for (char i='a'; i<='z'; i++) map[i]=i-'a'+10;
    n1=Transform(s1, radix);
    radix=Judge(n1, s2);
    if (radix==0) cout<<"Impossible";
    else cout<<radix;
}

//1、int大小不够要用long long
//2、要用二分查找，否则超时
//3、二分初始high时要限定大小不要去取LLONG_MAX,否则得不到正确答案
//4、考虑radix太大转换成10进制后值可能会溢出LLONG正数范围
int main(int argc, char *argv[])
{
    fun1();
}
