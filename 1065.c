#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1001
typedef long long LLONG;

void fun1()
{
    LLONG a,b,c;
    LLONG max=0x7FFFFFFFFFFFFFFF;//最大正数
    LLONG min=0x8000000000000000;//最小负数
    int n;
    int i,flag;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%lld%lld%lld", &a, &b, &c);
        //只有两种可能会溢出，而且都能确定结果
        if (a>0&&b>max-a) flag=1;//a+b正溢出，肯定比c大
        else if (a<0&&min-a>b) flag=0;//a+b负溢出，肯定比c小
        else flag=a+b>c?1:0;
        printf("Case #%d: %s\n", i, flag==1?"true":"false");
    }
}

void fun2()
{//判断溢出可以根据：1、ab都大于0但a+b<0;2、ab都小于0但a+b>0;

}

//要判断是否会溢出,两种方法：
//1、一种根据最大值和最小值来判断边界值，然后比较;--fun1
//2、一种是ab同号后相加是否变号；--fun2
int main(int argc, char *argv[])
{
   fun1();
}

