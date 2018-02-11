#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000
typedef long long LLONG;

int cmp(const void *a, const void *b)
{
    LLONG *x=(LLONG *)a;
    LLONG *y=(LLONG *)b;
    return *x>*y?1:-1;
}

void fun1()
{
    LLONG seq[MAX];
    LLONG n, p;
    int i,max=1;
    int left, right, mid;
    scanf("%lld%lld", &n, &p);
    if (n==0) {printf("0"); return;}
    for (i=0; i<n; i++)
        scanf("%lld", &seq[i]);
    qsort(seq, n, sizeof(seq[0]), cmp);
    for (i=0; i<n; i++) {
        //for (j=i+1; j<n&&seq[j]<=seq[i]*p; j++);
        left=i+1; right=n-1;
        while (left<=right) {//注意<=犯了几次错了
            mid=(left+right)/2;
            if (seq[mid]>seq[i]*p) right=mid-1;
            else left=mid+1;
        }
        max=left-i>max?left-i:max;
    }
    printf("%d", max);
}

//1、暴力破解有用例超时，改用二分法；注意<=
//2、虽然p在int范围内，但是乘以seq[i]就不一定了，用long long否则最后一个用例不过
int main(int argc, char *argv[])
{
   fun1();
}

