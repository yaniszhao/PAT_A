#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100001
#define MAXPAIR 1000000
#define INF 1e9

#define MIN(a,b) (a<b?a:b)

void fun1()
{//三个用例超时
    vector<int> dia, sum;
    int n,m;
    int i,j,tmp,min=INF;

    cin>>n>>m;
    dia.resize(n);
    sum.resize(n);
    for (i=0; i<n; i++) {
        scanf("%d", &dia[i]);
        if (i==0) sum[i]=dia[i];
        else sum[i]=sum[i-1]+dia[i];
    }

    for (i=0; i<n; i++) {
        for (j=i; j<n; j++) {
            tmp=sum[j]-sum[i]+dia[i];
            if (tmp>=m && tmp<min) min=tmp;
        }
    }

    for (i=0; i<n; i++) {
        for (j=i; j<n; j++) {
            tmp=sum[j]-sum[i]+dia[i];
            if (tmp>=min) break;
        }
        if (tmp==min) printf("%d-%d\n", i+1, j+1);
    }
}

void fun2()
{
    vector<int> dia, sum;
    int n,m;
    int i,j,tmp,min=INF;
    int low, high, mid;

    cin>>n>>m;
    dia.resize(n);
    sum.resize(n);
    for (i=0; i<n; i++) {
        scanf("%d", &dia[i]);
        if (i==0) sum[i]=dia[i];
        else sum[i]=sum[i-1]+dia[i];
    }

    for (i=0; i<n; i++) {
        low=i; high=n-1;
        while (low<=high) {//计算的是i到mid的总和
            mid=(low+high)/2;
            tmp=sum[mid]-sum[i]+dia[i];
            if (tmp==m) {min=m; break;}
            else if (tmp<m) low=mid+1;
            else {
                min=MIN(min, tmp);//在这里更新min循环完就不用更新了
                high=mid-1;
            }
        }

        if (min=m) break;
    }

    for (i=0; i<n; i++) {
        low=i; high=n-1;
        while (low<=high) {//计算的是i到mid的总和
            mid=(low+high)/2;
            tmp=sum[mid]-sum[i]+dia[i];
            if (tmp==min) break;
            else if (tmp>min) high=mid-1;
            else low=mid+1;
        }

        if (tmp==min) printf("%d-%d\n", i+1, mid+1);
    }
}

//先想到用sum有了fun1，然后发现fun1求tmp然后判断可以进行二分
//然后就有了fun2，注意求的是i到mid的总和
int main1(int argc, char *argv[])
{
    fun2();
}
