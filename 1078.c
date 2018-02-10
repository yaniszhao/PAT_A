#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10007//10000之后第一个素数是10007

int IsPrime(int n)
{
    int i;
    if (n==1) return 0;
    for (i=2; i<=sqrt(n); i++)
        if (n%i==0) return 0;
    return 1;
}

void fun1()
{
    int hash[MAX];
    int msize, n;
    int i, j;
    int val, size, pos;
    memset(hash, 0xFF, MAX*sizeof(hash[0]));//全设为-1
    scanf("%d%d", &msize, &n);
    for (size=msize; !IsPrime(size); size++);//重新定义size
    for (i=0; i<n; i++){
        scanf("%d", &val);
        for (j=0; j<size; j++) {//第一次也包含在for里面
            pos=(val+j*j)%size;
            if (hash[pos]==-1) {
                hash[pos]=val;
                if (i!=0) putchar(' ');
                printf("%d", pos);
                break;
            }
        }

        if (hash[pos]!=val) {
            if (i!=0) putchar(' ');
            putchar('-');
        }
    }
}

//1、如果第一次没找到，则步长从1加到size-1循环pos=(val+j*j)%size;
//2、注意是(key+step*step)%size而不是(key%size+step*step)
//3、一开始数据开小了，两个用例不过，当最大是10000时后面第一个素数是10007
//所以最小10007才能过，以后数据开的时候还是先开大点
int main(int argc, char *argv[])
{
   fun1();
}

