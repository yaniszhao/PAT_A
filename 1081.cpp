#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

typedef long long LLONG;

typedef struct {
    LLONG a;
    LLONG b;
} Rat;

LLONG Abs(LLONG a)
{
    return a>=0?a:-a;
}

LLONG gcd(LLONG a, LLONG b)
{
    return b==0?a:gcd(b, a%b);
}

void fun1()
{
    vector<Rat> rat;
    int n;
    LLONG i,mincom=1,gcdval,integer;
    Rat tmp;

    cin>>n;
    for (i=0; i<n; i++) {
        scanf("%lld/%lld", &tmp.a, &tmp.b);
        rat.push_back(tmp);
        gcdval=gcd(mincom, tmp.b);
        mincom=mincom*tmp.b/gcdval;
    }
    //求和
    tmp.a=0; tmp.b=mincom;
    for (auto it : rat)
        tmp.a+=it.a*mincom/it.b;
    if (tmp.a<0) {
        putchar('-');
        tmp.a=-tmp.a;
    }
    //约分
    gcdval=gcd(tmp.a, tmp.b);
    tmp.a/=gcdval;
    tmp.b/=gcdval;

    integer=tmp.a/tmp.b;
    tmp.a=tmp.a%tmp.b;

    if (integer!=0) {
        if (tmp.a==0) printf("%lld", integer);
        else printf("%lld %lld/%lld", integer, tmp.a, tmp.b);
    }
    else {
        if (tmp.a!=0) printf("%lld/%lld", tmp.a, tmp.b);
        else printf("0");//两个都为0，不加这个有4分用例不过
    }
}

void fun2()
{
    Rat sum, tmp;
    int n;
    LLONG i,mincom=1,gcdval,integer;

    cin>>n;
    sum.a=0; sum.b=1;
    for (i=0; i<n; i++) {
        scanf("%lld/%lld", &tmp.a, &tmp.b);
        //求和
        gcdval=gcd(sum.b, tmp.b);
        mincom=sum.b*tmp.b/gcdval;
        sum.a=sum.a*mincom/sum.b+tmp.a*mincom/tmp.b;
        sum.b=mincom;
        //约分
        gcdval=gcd(Abs(sum.a), sum.b);//只有分母才可能为负
        sum.a/=gcdval;
        sum.b/=gcdval;
    }

    if (sum.a<0) {//处理负号
        putchar('-');
        sum.a=-sum.a;
    }

    integer=sum.a/sum.b;
    sum.a=sum.a%sum.b;

    if (integer!=0) {
        if (sum.a==0) printf("%lld", integer);
        else printf("%lld %lld/%lld", integer, sum.a, sum.b);
    }
    else {
        if (sum.a!=0) printf("%lld/%lld", sum.a, sum.b);
        else printf("0");//两个都为0，不加这个有4分用例不过
    }
}

//1、fun1是先取数据然后一起求和约分，fun2是取完一个数据就求和约分
//2、fun1有一个用例不过，不知道是不是一起加的时候LLONG也不够，
//累加应该不可能，最小公倍数到时可能
//3、记住gcd函数
//4、这题据说不用LLONG会不过
int main(int argc, char *argv[])
{
    fun2();
}
