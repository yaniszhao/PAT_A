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
    int arr1[MAX], arr2[MAX];
    int n;
    int i,j,t,index,max;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &arr1[i]);
    for (i=0; i<n; i++) scanf("%d", &arr2[i]);
    //Insertion Sort
    for (i=2; i<=n; i++) {
        qsort(arr1, i, sizeof(arr1[0]), cmp);
        if (memcmp(arr1, arr2, n*sizeof(arr1[0]))!=0) continue;//比较n个，不是i个
        printf("Insertion Sort\n");
        //在做一次排序
        if (i<n) qsort(arr1, i+1, sizeof(arr1[0]), cmp);//都排好了就不排了
        for (j=0; j<n; j++)//arr1或arr2都可以
            if (j==0) printf("%d", arr1[j]);
            else printf(" %d", arr1[j]);
        return;
    }
    //Heap Sort
    printf("Heap Sort\n");
    //再做一次排序
    for (index=n-2; index>0&&arr2[index]>arr2[index-1]; index--);
    t=arr2[0]; arr2[0]=arr2[index]; arr2[index]=t;//swap
    t=arr2[0];
    for (i=0; 2*i+2<index||2*i+1<index;) {
        if (2*i+2<index) {//两个子树都可以比较要比较最大的
            max=arr2[2*i+2]>arr2[2*i+1]?2*i+2:2*i+1;
            if (t<arr2[max]) {//注意是拿t比较
                arr2[i]=arr2[max];
                i=max;
            }
            else break;
        }
        else if (2*i+1<index) {
            if (t<arr2[2*i+1]) {
                arr2[i]=arr2[2*i+1];
                i=2*i+1;
            }
            else break;
        }
    }
    arr2[i]=t;
    for (j=0; j<n; j++)//只能是arr2
        if (j==0) printf("%d", arr2[j]);
        else printf(" %d", arr2[j]);
}

//1、不需要模拟排序，只需要根据特性判断；但是堆排的下一次调整还是需要模拟
//2、判断插入排序可以根据前面有序，后面和输入相同进行判断，可参考liuchuo代码
//3、注意堆排向下调整的写法，我的写法有点生硬，还可以优化下
int main(int argc, char *argv[])
{
   fun1();
}

