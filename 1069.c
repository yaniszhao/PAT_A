#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10000

int cmp1(const void *a, const void *b)
{//从小到大
    char *x=(char *)a;
    char *y=(char *)b;
    return *x-*y;
}

int cmp2(const void *a, const void *b)
{//从大到小
    char *x=(char *)a;
    char *y=(char *)b;
    return *y-*x;
}

int GetLow(int n)
{
    char s[5];
    sprintf(s, "%04d", n);
    qsort(s, 4, sizeof(s[0]), cmp1);
    return atoi(s);
}

int GetBig(int n)
{
    char s[5];
    sprintf(s, "%04d", n);
    qsort(s, 4, sizeof(s[0]), cmp2);
    return atoi(s);
}

void fun1()
{//遇到6174要结束我没结束，我这个不符合题意
    int n;
    int big,low;
    scanf("%d", &n);
    big=GetBig(n);
    low=GetLow(n);
    while (big-low!=n) {
        printf("%04d - %04d = %04d\n", big, low, big-low);
        n=big-low;
        big=GetBig(n);
        low=GetLow(n);
    }
}

void fun2()
{
    int n;
    int big,low;
    scanf("%d", &n);
    do {
        big=GetBig(n);
        low=GetLow(n);
        printf("%04d - %04d = %04d\n", big, low, big-low);
        n=big-low;
    } while (big-low!=0&&big-low!=6174);
}

//1、注意6174是个魔数，我一开始以为是大-小只到它和上一次的重复
//2、输入为6174也要打印一次，故用do...while
int main(int argc, char *argv[])
{
   fun2();
}

