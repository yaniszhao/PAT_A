#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001
#define MAXPAIR 1000000
#define INF 1e9


void fun1()
{//用了两个2重循环，时间复杂度有点大
    int dia[MAX];
    int n, amount;
    int i,j,min=INF,tmp;
    scanf("%d%d", &n, &amount);
    for (i=1; i<=n; i++) scanf("%d", &dia[i]);

    for (i=1; i<=n; i++) {//确认值是多少
        tmp=0;
        for (j=i; j<=n; j++) {
            tmp+=dia[j];
            if (tmp>=amount) {
                if (tmp<min) min=tmp;
                break;//不提前退出还有用例不过
            }
        }
    }

    for (i=1; i<=n; i++) {//得到对应的子串
        tmp=0;
        for (j=i; j<=n; j++) {
            tmp+=dia[j];
            if (tmp>=min) break;
        }
        if (tmp==min) printf("%d-%d\n", i, j);
    }
}

void fun2()
{//用了多的空间节约了一个循环，还是有两个用例不过
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

void fun3()
{
    int dia[MAX], sum[MAX];
    int n, m;
    int i,j,min=INF,tmp;
    int low, high, mid;

    scanf("%d%d", &n, &m);
    for (i=1; i<=n; i++) {
        scanf("%d", &dia[i]);
        if (i==1) sum[i]=dia[i];
        else sum[i]=sum[i-1]+dia[i];
    }

    for (i=1; i<=n; i++) {//确认值是多少
        low=i; high=n;
        while (low<=high) {
            mid=(low+high)/2;
            tmp=sum[mid]-sum[i]+dia[i];
            if (tmp==m) {min=m; break;}
            else if (tmp<m) low=mid+1;
            else {
                if (tmp<min) min=tmp;
                high=mid-1;
            }
        }

        if (min==m) break;//找到了可以直接退出
    }

    for (i=1; i<=n; i++) {//得到对应的子串
        low=i; high=n;
        while (low<=high) {
            mid=(low+high)/2;
            tmp=sum[mid]-sum[i]+dia[i];
            if (tmp==min) break;
            else if (tmp<min) low=mid+1;
            else high=mid-1;
        }

        if (tmp==min) printf("%d-%d\n", i, mid);
    }
}

//1、fun1和fun2在之前写的了，一直没AC，后来想到用sum，然后在cpp中完成了
//2、在cpp中先用sum然后想到了二分，然后在c中实现
//3、注意二分求和是i到mid的总和
int main(int argc, char *argv[])
{
    fun3();
}
