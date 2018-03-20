#include <iostream>
#include<string>
#include <cmath>
using namespace std;

int IsPrime(int n)
{
    if (n<2) return 0;//注意加判断
    for (int i=2; i<=sqrt(n); i++)
        if (n%i==0) return 0;
    return 1;
}

int Convert(int n, int radix)
{
    string s;
    while (n>0) {//得到的结果正好是翻转过后的
        s+=to_string(n%radix);
        n/=radix;
    }
    for (auto it : s)//换成10进制
        n=n*radix+it-'0';
    return n;
}

void fun1()
{
    int n,d;
    cin>>n;
    while (n>=0) {
        cin>>d;
        int flag=1;
        if (n==0 || !IsPrime(n)) flag=0;
        else {
            n=Convert(n, d);
            flag=IsPrime(n);
        }
        printf("%s\n", flag?"Yes":"No");
        cin>>n;
    }
}

//简单题，注意1不是素数
int main(int argc, char *argv[])
{
    fun1();
}
