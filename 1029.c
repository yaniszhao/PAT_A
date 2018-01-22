#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000

void fun1()
{
    long *s1;//用栈分配会超出大小
    long *s2;
    int n1, n2;
    int i=0,j=0,k;
    long med;

    //每行的开始是个数，如果没有个数按下面的读取
//    char c;
//    do {
//        scanf("%ld%c", &s1[n1++], &c);
//    } while(c!='\n');
//
//    do {
//        scanf("%ld%c", &s2[n2++], &c);
//    } while(c!='\n');
    
    scanf("%d", &n1);
    s1=malloc(n1*sizeof(*s1));
    for (i=0; i<n1; i++)
        scanf("%ld", &s1[i]);
    
    scanf("%d", &n2);
    s2=malloc(n2*sizeof(*s2));
    for (i=0; i<n2; i++)
        scanf("%ld", &s2[i]);
    
    //要考虑单边是否超过，不能只做第一次循环
    //(n1+n2+1)/2是第几个，(n1+n2-1)/2是下标
    for (k=1,i=0,j=0; k<(n1+n2+1)/2 && i<n1 && j<n2; k++)
        s1[i]<=s2[j]?i++:j++;
    while (i==n1 && j+i<(n1+n2+1)/2-1) j++;
    while (j==n2 && j+i<(n1+n2+1)/2-1) i++;
    
    //要考虑单边是否超过,不能只用s1[i]<=s2[j]?s1[i]:s2[j]
    if (i==n1) med=s2[j];
    else if (j==n2) med=s1[i];
    else med=s1[i]<=s2[j]?s1[i]:s2[j];
    
    printf("%ld", med);
}

//1、用一个数组全部装下
//2、排序，但是普通排序可能超时，用快排应该可以，如果stl的很方便
//3、第(n1+n2-1)/2就是答案
void fun2()
{
    
}

//要考虑单边是否超过
int main(int argc, char *argv[])
{
    fun1();
}
