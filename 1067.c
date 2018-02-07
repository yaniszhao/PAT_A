#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000

int IsInc(int arr[], int n)
{
    int i;
    for (i=1; i<n; i++)
        if (arr[i]<arr[i-1])
            return 0;
    return 1;
}

int FindVal(int arr[], int n, int val)
{
    int i;
    for (i=0; i<n; i++)
        if (arr[i]==val)
            return i;
    return -1;
}

void Swap(int arr[], int x, int y)
{
    int t;
    t=arr[x];
    arr[x]=arr[y];
    arr[y]=t;
}

void fun1()
{//两个用例超时
    int arr[MAX];
    int n;
    int i,j,cnt=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    while (IsInc(arr, n)==0) {
        if (arr[0]==0) {//0已经在0号位了，但没有全部排好序
            for (i=1; arr[i]==i; i++);
            Swap(arr, 0, i);
            cnt++;
        }
        while (arr[0]!=0) {//一直交换到0在0号位
            i=FindVal(arr, n, 0);
            j=FindVal(arr, n, i);
            Swap(arr, i, j);
            cnt++;
        }
    }
    printf("%d", cnt);
}
//===============================================
void fun2()
{//做了少量优化，还是两个超时
    int arr[MAX];
    int n;
    int i,j,cnt=0,index=1;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    while (IsInc(arr, n)==0) {
        if (arr[0]==0) {//0已经在0号位了，但没有全部排好序
//            for (i=1; arr[i]==i; i++);
//            Swap(arr, 0, i);
            for (; index<n&&arr[index]==index; index++);
            Swap(arr, 0, index);
            cnt++;
        }
        //每次循环减少了FindVal函数和Swap函数
        //每次相当于把0提出来，然后空出的位置填上对应的值，最后把0补到对应位置
        i=FindVal(arr, n, 0);
        while (i!=0) {
            j=FindVal(arr, n, i);
            //Swap(arr, i, j);
            arr[i]=i;
            cnt++;
            i=j;
        }
        arr[0]=0;
    }
    printf("%d", cnt);
}

//关键函数我把FindVal和Swap都优化了，还是有一个超时
//改了查找第一个不相等值的for循环，时间瞬间减少了很多
void fun3()
{
    int map[MAX];
    int arr[MAX];
    int n;
    int i,j,index=1;
    int badnum=0,cnt=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &arr[i]);
        map[arr[i]]=i;
        if (arr[i]!=i) badnum++;
    }
    while (badnum!=0) {
        if (arr[0]==0) {//0已经在0号位了，但没有全部排好序
            //改了这个for循环，时间瞬间减少了很多
            //for (i=1; arr[i]==i; i++);
            for (; index<n&&arr[index]==index; index++);
            Swap(arr, 0, index);
            cnt++;
            Swap(map, 0, index);//位置也要交换
            badnum++;//另外一个本来就是乱的，所以只有0又乱故只加一
        }
        //这个关键函数我把FindVal和Swap都优化了
        i=map[0];
        while (i!=0) {
            j=map[i];
            arr[i]=i; map[i]=i;
            cnt++; badnum--;
            i=j;
        }
        arr[0]=0; map[0]=0;
        badnum--;
    }
    printf("%d", cnt);
}

//fun1根据自己想的方法写的简单代码,简单好懂
//fun2对下标的查找和连续数值的交换做了优化
//fun3减掉了查找函数，减掉了判别是否完成的函数，对交换也像fun2做了处理,还有一个用例不过，
//想了下只有找出第一个不相等的值的for循环可以优化了，但是没想出来，
//看到liuchuo的代码才搞定的,改了那个点时间减少了很多，但是fun2改了这点还是不过，
//所以fun3的其他连个改动也很重要
//这道题就是思路不变，然后代码一步步改进的过程
int main(int argc, char *argv[])
{
   fun3();
}

