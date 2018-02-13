#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

void fun1()
{
    int a[MAX], b[MAX], bak[MAX];
    int n;
    int i,j,flag,step;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &a[i]);
    for (i=0; i<n; i++) scanf("%d", &b[i]);

    memcpy(bak, a, n*sizeof(bak[0]));
    for (i=1; i<n; i++) {
        qsort(bak, i+1, sizeof(bak[0]), cmp);//排一次序
        flag=1;
        for (j=0; j<n; j++)
            if (bak[j]!=b[j]) {flag=0; break;}
        if (flag==1) {//满足要求
            printf("Insertion Sort\n");
            //再排一次打印并退出
            qsort(bak, i+2, sizeof(bak[0]), cmp);
            printf("%d", bak[0]);
            for (j=1; j<n; j++) printf(" %d", bak[j]);
            return;
        }
    }

    memcpy(bak, a, n*sizeof(bak[0]));
    for (step=2; step<=n; step*=2) {
        if (step>n) step=n;
        for (i=0; i<n; i+=step)//排一次序，i相当于start,注意超出n的情况
            if (i+step>n) qsort(&bak[i], n-i, sizeof(bak[0]), cmp);
            else qsort(&bak[i], step, sizeof(bak[0]), cmp);
        flag=1;
        for (j=0; j<n; j++)
            if (bak[j]!=b[j]) {flag=0; break;}
        if (flag==1) {//满足要求
            printf("Merge Sort\n");
            //再排一次打印并退出
            step*=2;
            if (step>n) step=n;
            for (i=0; i<n; i+=step)
                if (i+step>n) qsort(&bak[i], n-i, sizeof(bak[0]), cmp);
                else qsort(&bak[i], step, sizeof(bak[0]), cmp);
            printf("%d", bak[0]);
            for (j=1; j<n; j++) printf(" %d", bak[j]);
            return;
        }
    }
}

//1、插入排序是每次前k个有序，归并是相邻step个有序每次step扩大一倍直至到n
//2、根据特性排序后比较，一次AC
//3、两个地方重复代码都可以优化但是也没什么必要
//4、插入排序如果每次都不相等不会退出，可以考虑提前退出
//5、可以根据判断是否是插入排序就可以很快得到结果，也能很好的得到下一次插入排序的结果
//但是排除插入之后，归并的下一次结果的判断还是麻烦，所以当前这个方法暴力但是思路清晰
//6、插入排序的判断可以模拟然后判断，但是归并的不行，因为正常情况代码是递归的，除非用非递归的实现方法
int main(int argc, char *argv[])
{
   fun1();
}

