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
    int minmax, sum=0, integer;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d/%d", &a[i], &b[i]);
        if (b[i]==0) {n--; i--; continue;}//处理分母为0
        if (i==0) {minmax=b[i]; continue;}

        if (b[i]>minmax&&b[i]%minmax!=0) {
            for (j=1; j<=minmax&&j*b[i]%minmax!=0; j++);
            minmax=j*b[i];
        }
        else if (b[i]<minmax&&minmax%b[i]!=0) {
            for (j=1; j<=b[i]&&j*minmax%b[i]!=0; j++);
            minmax=j*minmax;
        }
    }
    //得到分子
    for (i=0; i<n; i++) sum+=a[i]*minmax/b[i];
    if (sum==0) {printf("0"); return;}
    //如果sum太大，可以先得到整数
    integer=sum/minmax;
    sum=sum%minmax;
    if (integer>0) printf("%d", integer);
    //约分
    min=abs(sum)>abs(minmax)?abs(minmax):abs(sum);
    for (i=2; i<=min; i++)
        if (sum%i==0&&minmax%i==0) {
            sum/=i; minmax/=i;
            min/=i; i--;
        }
    if (integer!=0&&sum!=0) putchar(' ');
    if (sum!=0) printf("%d/%d", sum, minmax);

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
    LLONG minmax, sum=0, integer;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%lld/%lld", &a[i], &b[i]);
        min=gcd(Abs(a[i]), Abs(b[i]));
        a[i]/=min; b[i]/=min;
        if (i==0) {minmax=b[i]; continue;}

        if (b[i]>minmax&&b[i]%minmax!=0) {
            for (j=1; j<=minmax&&j*b[i]%minmax!=0; j++);
            minmax=j*b[i];
        }
        else if (b[i]<minmax&&minmax%b[i]!=0) {
            for (j=1; j<=b[i]&&j*minmax%b[i]!=0; j++);
            minmax=j*minmax;
        }
    }
    //得到分子
    for (i=0; i<n; i++) sum+=a[i]*minmax/b[i];
    if (sum==0) {printf("0"); return;}
    //如果sum太大，可以先得到整数
    integer=sum/minmax;
    sum=sum%minmax;
    if (integer>0) printf("%lld", integer);
    //约分
    min=gcd(Abs(sum), Abs(minmax));
    sum/=min; minmax/=min;
    if (integer!=0&&sum!=0) putchar(' ');
    if (sum!=0) printf("%lld/%lld", sum, minmax);

}

void fun3()
{//AC代码
    LLONG suma=0, sumb=1, tmpa, tmpb;
    int n;
    LLONG i,gcdval;
    LLONG mincom, integer;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%lld/%lld", &tmpa, &tmpb);
        //求和
        gcdval=gcd(sumb, tmpb);
        mincom=sumb*tmpb/gcdval;
        suma=suma*mincom/sumb+tmpa*mincom/tmpb;
        sumb=mincom;
        //约分
        gcdval=gcd(Abs(suma), sumb);//只有分子可能为负
        suma/=gcdval;
        sumb/=gcdval;
    }

    if (suma<0) {
        putchar('-');
        suma=-suma;
    }

    integer=suma/sumb;
    suma=suma%sumb;

    if (integer!=0) {
        if (suma==0) printf("%lld", integer);
        else printf("%lld %lld/%lld", integer, suma, sumb);
    }
    else {
        if (suma!=0) printf("%lld/%lld", suma, sumb);
        else printf("0");//两个都为0，不加这个有4分用例不过
    }
}

//1、注意格式，空格什么打印要判断清楚
//2、用int范围不够，要用long long
//3、不在累加的时候约分会有个用例不过
//4、fun3根据cpp写的代码写的AC代码
int main(int argc, char *argv[])
{
   fun3();
}

