#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 30
typedef long long LLONG;

typedef struct {
    LLONG top;
    LLONG bot;
} Rat;

LLONG gcd(LLONG a, LLONG b)
{
    return b==0?a:gcd(b, a%b);
}

LLONG Abs(LLONG a)
{
    return a>=0?a:-a;
}

void FormatPrint(Rat rat)
{
    LLONG integer, mod, gcdval;
    int flag=0;
    //判别分母为0和负号
    if (rat.bot==0) {printf("Inf"); return;}
    if (rat.top<0) flag=1;//有负号
    rat.top=Abs(rat.top);
    if (flag) printf("(-");//要不要考虑-0?
    //得到整数和模
    gcdval=gcd(rat.top, rat.bot);
    rat.top/=gcdval;
    rat.bot/=gcdval;
    integer=rat.top/rat.bot;
    mod=rat.top%rat.bot;
    //打印
    if (integer==0&&mod==0) printf("0");
    else if (integer!=0&&mod==0) printf("%lld", integer);
    else if (integer==0&&mod!=0) printf("%lld/%lld", mod, rat.bot);
    else printf("%lld %lld/%lld", integer, mod, rat.bot);

    if (flag) putchar(')');
}

void fun1()
{
    Rat a,b;
    Rat sum, diff, prod, quot;
    LLONG gcdval, mincom;
    scanf("%lld/%lld", &a.top, &a.bot);
    scanf("%lld/%lld", &b.top, &b.bot);
    gcdval=gcd(a.bot, b.bot);
    mincom=a.bot*b.bot/gcdval;
    //加法
    sum.top=a.top*mincom/a.bot+b.top*mincom/b.bot;
    sum.bot=mincom;
    FormatPrint(a); printf(" + ");
    FormatPrint(b); printf(" = ");
    FormatPrint(sum); putchar('\n');
    //减法
    diff.top=a.top*mincom/a.bot-b.top*mincom/b.bot;
    diff.bot=mincom;
    FormatPrint(a); printf(" - ");
    FormatPrint(b); printf(" = ");
    FormatPrint(diff); putchar('\n');
    //乘法
    prod.top=a.top*b.top;
    prod.bot=a.bot*b.bot;
    FormatPrint(a); printf(" * ");
    FormatPrint(b); printf(" = ");
    FormatPrint(prod); putchar('\n');
    //除法
    quot.top=a.top*b.bot;
    quot.bot=a.bot*b.top;
    if ((quot.top<0&&quot.bot<0)||(quot.top>0&&quot.bot<0)) {
        //处理负号,默认是只有分子才可能有负数
        quot.top=-quot.top;
        quot.bot=-quot.bot;
    }
    FormatPrint(a); printf(" / ");
    FormatPrint(b); printf(" = ");
    FormatPrint(quot); putchar('\n');
}

//主要代码是格式打印那里，处理好负号、整数和余模，然后根据它们确定打印格式
//不该成long long最后两个用例不过，一改就过了
int main(int argc, char *argv[])
{
   fun1();
}

