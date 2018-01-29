#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001
#define MAXPAIR 1000000
#define INF 1e9

//用了两个2重循环，时间复杂度有点大
//三个用例会超时
void fun1()
{
    int dia[MAX];
    int n, amount;
    int i,j,min=INF,tmp;
    scanf("%d%d", &n, &amount);
    for (i=1; i<=n; i++) scanf("%d", &dia[i]);
    
    for (i=1; i<=n; i++) {
        tmp=0;
        for (j=i; j<=n; j++) {
            tmp+=dia[j];
            if (tmp>=amount && tmp<min) min=tmp;
        }
    }
    
    for (i=1; i<=n; i++) {
        tmp=0;
        for (j=i; j<=n; j++) {
            tmp+=dia[j];
            if (tmp>=min) break;
        }
        if (tmp==min) printf("%d-%d\n", i, j);
    }
}

//用了多的空间节约了一个循环
//还是有两个用例不过
void fun2()
{
    int dia[MAX];
    int *a, *b, cnt=0;//要开的足够大，否则还有用例不过，栈大小不够
    int n, amount;
    int i,j,min=INF,tmp;
    a=(int *)malloc(MAXPAIR*sizeof(a[0]));
    b=(int *)malloc(MAXPAIR*sizeof(b[0]));
    scanf("%d%d", &n, &amount);
    for (i=1; i<=n; i++) scanf("%d", &dia[i]);
    for (i=1; i<=n; i++) {
        tmp=0;
        for (j=i; j<=n; j++) {
            tmp+=dia[j];
            if (tmp>=amount) break;
        }
        
        if (tmp==amount) {
            if (min!=amount) {//等于amount第一次
                min=amount;
                cnt=0;
            }
            a[cnt]=i;
            b[cnt]=j;
            cnt++;
        }
        else if (tmp>amount && tmp<=min) {
            if (tmp!=min) {//比min小且第一次
                min=tmp;
                cnt=0;
            }
            a[cnt]=i;
            b[cnt]=j;
            cnt++;
        }
    }
    for (i=0; i<cnt; i++)
        printf("%d-%d\n", a[i], b[i]);
}

int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}
