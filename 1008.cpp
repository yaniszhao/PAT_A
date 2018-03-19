#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void fun1()
{
    int n, cur=0, need, sum=0;
    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>need;
//        if (need>cur) sum+=(6*(need-cur)+5);
//        else if (need<cur) sum+=(4*(cur-need)+5);
//        else sum+=5;//去掉这行就不行，说明可能有两个相邻层数是一样的，所以可以简化成下面格式
        if (need>cur) sum+=(6*(need-cur)+5);
        else sum+=(4*(cur-need)+5);
        cur=need;
    }
    cout<<sum;
}

//简单题，但需要考虑两个相邻层数是一样的情况要等5秒
int main(int argc, char *argv[])
{
    fun1();
}
