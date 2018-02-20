#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 12

int Factorial(int n)
{
    int i,ans=1;
    for (i=2; i<=n; i++) ans*=i;
    return ans;
}

void fun1()
{
    int map[MAX+1];
    int n;
    int i,j,k,mul;
    for (i=1; i<=MAX; i++) map[i]=Factorial(i);
    scanf("%d", &n);
    for (i=MAX-1; i>=2; i--) {
        for (j=1; j<=MAX-i; j++) {//若j从2开始，但要除map[j-1]，所以j还是从1开始
            mul=map[j+i]/map[j];
            if (n%mul==0) {
                printf("%d\n%d", i, j+1);
                for (k=2; k<=i; k++) printf("*%d", j+k);
                return;
            }
        }
    }
    //走到这里要么是质数，要么是是两个不连续数的积
    for (i=2; i<=sqrt(n);i++) {
        if (n%i==0) {
            printf("1\n%d", i);
            return;
        }
    }
    printf("1\n%d", n);
}

//1、因为2^31小于13！所以最大是12！乘以一个数，而12！长度是11所以长度从11递减的判断
//2、因为长度一样时，取最小的乘积，所以mul从小到大循环
//3、如果连2个连续的乘积都没有，要么是质数，要么是是两个不连续数的积
int main(int argc, char *argv[])
{
   fun1();
}

