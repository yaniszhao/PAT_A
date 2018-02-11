#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100
typedef long long LLONG;

void fun1()
{
    int a[MAX], b[MAX];
    int n;
    int i,j,min;
    int maxcom, sum=0, integer;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d/%d", &a[i], &b[i]);
        if (b[i]==0) {n--; i--; continue;}//处理分母为0
        if (i==0) {maxcom=b[i]; continue;}

        if (b[i]>maxcom&&b[i]%maxcom!=0) {
            for (j=1; j<=maxcom&&j*b[i]%maxcom!=0; j++);
            maxcom=j*b[i];
        }
        else if (b[i]<maxcom&&maxcom%b[i]!=0) {
            for (j=1; j<=b[i]&&j*maxcom%b[i]!=0; j++);
            maxcom=j*maxcom;
        }
    }
    //得到分子
    for (i=0; i<n; i++) sum+=a[i]*maxcom/b[i];
    if (sum==0) {printf("0"); return;}
    //如果sum太大，可以先得到整数
    integer=sum/maxcom;
    sum=sum%maxcom;
    if (integer>0) printf("%d", integer);
    //约分
    min=abs(sum)>abs(maxcom)?abs(maxcom):abs(sum);
    for (i=2; i<=min; i++)
        if (sum%i==0&&maxcom%i==0) {
            sum/=i; maxcom/=i;
            min/=i; i--;
        }
    if (integer!=0&&sum!=0) putchar(' ');
    if (sum!=0) printf("%d/%d", sum, maxcom);

}
//================================================
LLONG Abs(LLONG a)
{
    return a>=0?a:-a;
}

LLONG gcd(LLONG a, LLONG b)
{
    return b==0?a:gcd(b, a%b);
}

void fun2()
{
    LLONG a[MAX], b[MAX];
    int n;
    LLONG i,j,min;
    LLONG maxcom, sum=0, integer;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%lld/%lld", &a[i], &b[i]);
        min=gcd(Abs(a[i]), Abs(b[i]));
        a[i]/=min; b[i]/=min;
        if (i==0) {maxcom=b[i]; continue;}

        if (b[i]>maxcom&&b[i]%maxcom!=0) {
            for (j=1; j<=maxcom&&j*b[i]%maxcom!=0; j++);
            maxcom=j*b[i];
        }
        else if (b[i]<maxcom&&maxcom%b[i]!=0) {
            for (j=1; j<=b[i]&&j*maxcom%b[i]!=0; j++);
            maxcom=j*maxcom;
        }
    }
    //得到分子
    for (i=0; i<n; i++) sum+=a[i]*maxcom/b[i];
    if (sum==0) {printf("0"); return;}
    //如果sum太大，可以先得到整数
    integer=sum/maxcom;
    sum=sum%maxcom;
    if (integer>0) printf("%lld", integer);
    //约分
    min=gcd(Abs(sum), Abs(maxcom));
    sum/=min; maxcom/=min;
    if (integer!=0&&sum!=0) putchar(' ');
    if (sum!=0) printf("%lld/%lld", sum, maxcom);

}

//注意格式，空格什么打印要判断清楚
//用int范围不够，要用long long
//还有个用例不过
int main(int argc, char *argv[])
{
   fun2();
}

