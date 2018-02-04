#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000//是long int范围内的素数最大个数我随便估的

typedef struct {
    int prime;
    int cnt;
} Node;

int IsPrime(int n)
{
    int i;
    if (n==1) return 0;
    for (i=2; i<=sqrt(n); i++)
        if (n%i==0) return 0;
    return 1;
}

int FirstPrime(int num, int n)
{
    int i;
    for (i=num; i<=n; i++)
        if (IsPrime(i)) return i;
    return 0;
}

void fun1()
{
    Node primes[MAX];
    int tail=0;
    int n;
    int i=2, p;

    scanf("%d", &n);
    if (n==1) printf("1=1");//要对1做处理否则有个用例不过
    else printf("%d=", n);

    while (n!=1) {
        p=FirstPrime(i, n);
        //肯定能找到p，不用判断if(p)，因为要么有，要么也是它自己
        if (n%p==0) {
            n=n/p;
            if (tail>0 && primes[tail-1].prime==p) primes[tail-1].cnt++;
            else {primes[tail].prime=p;  primes[tail].cnt=1; tail++;}
            i=p;
        }
        else i=p+1;
    }

    //打印可以放到while循环里打印节省了primes空间，但处理很麻烦
    if (tail>0) {
        printf("%d", primes[0].prime);
        if (primes[0].cnt>1) printf("^%d", primes[0].cnt);
    }
    for (i=1; i<tail; i++) {
        printf("*%d", primes[i].prime);
        if (primes[i].cnt>1) printf("^%d", primes[i].cnt);
    }

}

//1、之前考虑过hash，但是也空间肯定不够，也考虑了2到n的所有素数先求出来，感觉也会浪费空间和时间
//2、我这种类贪心算法开始以为复杂度高了，没想到时间非常短，可能是因为根据当前状态即在增加i又在减少n
//3、有素数就考虑要对1做处理，比如1015
int main(int argc, char *argv[])
{
   fun1();
}

