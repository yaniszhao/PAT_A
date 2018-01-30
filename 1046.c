#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001
#define MAXPAIR 10000
#define INF 1e7

void fun1()
{//一个用例超时
    int edge[MAX];
    int pair1[MAXPAIR], pair2[MAXPAIR];
    int n,m;
    int i, j, k;
    int num, len1, len2;
    scanf("%d", &n);
    for (i=1; i<=n; i++) scanf("%d", &edge[i]);
    scanf("%d", &m);
    for (i=0; i<m; i++) scanf("%d%d", &pair1[i], &pair2[i]);
    for (i=0; i<m; i++) {
        num=(pair2[i]>pair1[i])?(pair2[i]-pair1[i]):(pair1[i]-pair2[i]);
        for (j=0, len1=0; j<num; j++) {//按小到大顺序走一次
            k=(pair2[i]>pair1[i])?(pair1[i]+j):(pair2[i]+j);
            if (k>n) k=k-n;
            len1+=edge[k];
        }
        
        num=n-num;
        for (j=0, len2=0; j<num; j++) {//按大到小顺序走一次
            k=(pair2[i]>pair1[i])?(pair2[i]+j):pair1[i]+j;
            if (k>n) k=k-n;
            len2+=edge[k];
        }
        printf("%d\n", (len1<len2?len1:len2));
    }
}

void fun2()
{
    int sum[MAX];
    int pair1[MAXPAIR], pair2[MAXPAIR];
    int n,m;
    int i;
    int len1, len2;
    scanf("%d", &n);
    sum[0]=0;
    for (i=1; i<=n; i++) {
        scanf("%d", &sum[i]);
        sum[i]=(i==1)?sum[i]:(sum[i]+sum[i-1]);
    }
    scanf("%d", &m);
    for (i=0; i<m; i++) scanf("%d%d", &pair1[i], &pair2[i]);
    
//    for (i=0; i<m; i++) {
//        if (pair1[i]<pair2[i]) {
//            len1=sum[pair2[i]-1]-sum[pair1[i]-1];
//            len2=sum[n]-len1;
//        }
//        else {
//            len1=sum[pair1[i]-1]-sum[pair2[i]-1];
//            len2=sum[n]-len1;
//        }
//        printf("%d\n", (len1<len2?len1:len2));
//    }
    
        for (i=0; i<m; i++) {//相比上面更简便的方法
            len1= (pair1[i]<pair2[i]) ? \
                (sum[pair2[i]-1]-sum[pair1[i]-1]) : \
                (sum[pair1[i]-1]-sum[pair2[i]-1]);
            printf("%d\n", (len1<(sum[n]-len1))?len1:(sum[n]-len1));
        }
}

//1、大前面换成小在前面，这样好计算小->大的距离，然后就是比较这个距离和全部距离减这个距离
//2、一开始我没注意到小->大加大到小就是全部距离
//3、不管大到小还是小到大都转换成小到大比较好计算，否则要考虑超过最值的时候的处理
//4、每次记录距离之和比记录两边要好，否则每次还要做一次循环计算
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}
