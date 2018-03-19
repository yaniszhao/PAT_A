#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int StrToInt(string s)
{//可以在读取的时候通过scanf来直接得到小时分钟和秒
    int sum=0;
    sum=stoi(s.substr(0,2))*3600;
    sum+=stoi(s.substr(3,5))*60;
    sum+=stoi(s.substr(6,8));
    return sum;
}

void fun1()
{
    map<int, string> mapin;
    map<int, string> mapout;
    int m;
    cin>>m;
    for (int i=0; i<m; i++) {
        string name,sin,sout;
        cin>>name>>sin>>sout;
        mapin[StrToInt(sin)]=name;
        mapout[StrToInt(sout)]=name;
    }
    cout<<mapin.begin()->second<<' '<<mapout.rbegin()->second;
}

//1、简单题，注意时间化整形可以通过scanf直接得到整数
//2、可以一边读一边比较数据，每次保留最早来和最迟离开的就可以，可以节约很多空间
int main(int argc, char *argv[])
{
    fun1();
}
