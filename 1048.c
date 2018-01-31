#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MAXVAL 1001//钱的范围,501不对，因为m<=1000，当v1小于500时v2访问会越界？


int cmp(const void *a, const void *b)
{
    int x=*(int*)a;
    int y=*(int*)b;
    //return x>y?1:-1;//错误要返回-1，返回0也会排不成功
    return x-y;//还是这样写好点，因为会返回正数、0、负数三种情况，准确点
}

void Sort(int arr[], int n)
{
    int i,j,min,t;
    for (i=0; i<n-1; i++) {
        min=i;
        for (j=i+1; j<n; j++)
            if (arr[j]<arr[min]) min=j;
        t=arr[i];
        arr[i]=arr[min];
        arr[min]=t;
    }
}

int Partition(int arr[], int n)
{
    int t=arr[0];
    int i=0,j=n-1;
    while (i<j) {
        while (i<j && arr[j]>=t) j--;
        arr[i]=arr[j];
        while (i<j && arr[i]<=t) i++;
        arr[j]=arr[i];
    }
    arr[i]=t;
    return i;
}

void QuickSort(int arr[], int n)
{
    int pivot;
    if (n==0 || n==1) return;
    pivot=Partition(arr, n);
    QuickSort(arr, pivot);
    QuickSort(&arr[pivot+1], n-pivot-1);
}

void fun1()
{//暴力破解，两个用例超时,qsort也要超时
    int coins[MAX];
    int n,m;
    int i,j;
    int x=-1,y=-1;
    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++)
        scanf("%d", &coins[i]);
    //Sort(coins, n);
    qsort(coins, n, sizeof(int), cmp);
    for (i=0; i<n-1; i++) {
        for (j=i+1; j<n; j++)
            if (coins[i]+coins[j]==m) {x=i; y=j; break;}
        if (x!=-1) break;
    }
    if (x==-1) printf("No Solution");
    else printf("%d %d", coins[x], coins[y]);
}

//===============================================================

//一开始还是有两个不过，但是我已经是O(N)了，所以问题肯定在排序上，然后改进排序
//但是快排还是有超时,就只有用qsort了
void fun2()
{
    int map[MAXVAL]={0};
    int coins[MAX];
    int n,m;
    int i,j;
    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++) {
        scanf("%d", &coins[i]);
        map[coins[i]]++;
    }
    //QuickSort(coins, n);
    qsort(coins, n, sizeof(int), cmp);
    for (i=0; i<n-1; i++) {//liuchuo是去直接遍历map，没必要，我这种要少遍历一些数据
        map[coins[i]]--;//可能有重复的，要减后面判断
        if (m>coins[i] && map[m-coins[i]]>0)
            break;
        map[coins[i]]++;//要重复使用，加回去
    }
    if (i==n-1) printf("No Solution");
    else printf("%d %d", coins[i], m-coins[i]);
}


//1、暴力破解不能全过，即使用qsort
//2、改进后程序O(N)还超时，改用qsort
//3、qosrt的比较函数要注意返回值，否者可能会排序失败
//4、这题的钱的最大值要注意是1000不是500，否者一个错误
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}
