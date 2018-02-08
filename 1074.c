#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000

typedef struct {
    int addr;
    int key;
    int next;
} Node;

void Reverse(Node arr[], int st, int ed)
{
    int i, mid=(st+ed)/2;
    Node tmp;
    for (i=st; i<=mid; i++) {
        tmp=arr[i];
        arr[i]=arr[ed+st-i];//ed-(i-st);
        arr[ed+st-i]=tmp;
    }
}

void fun1()
{
    Node tmp[MAX];
    Node list[MAX];
    int start, n, k;
    int i, addr, cnt;

    scanf("%d%d%d", &start, &n, &k);
    for (i=0; i<n; i++) {//接收数据，根据地址放置
        scanf("%d", &addr);
        tmp[addr].addr=addr;
        scanf("%d%d", &tmp[addr].key, &tmp[addr].next);
    }

    //做成链表
    for (i=0, addr=start; i<n&&addr!=-1; i++) {
        list[i]=tmp[addr];
        addr=list[i].next;
    }
    cnt=i;//考虑有些可能不在一条链上,只记录有效的

    //反向赋值，多次翻转先翻转再赋值好点
    k=k>cnt?cnt:k;
//    list[0].next=list[k-1].next;//不要用list[k].addr因为可能不存在
//    for (i=k-1; i>0; i--)
//        list[i].next=list[i-1].addr;
//    Reverse(list, 0, k-1);
    for (n=cnt/k, i=0; i<n; i++)//翻转后再赋值
        Reverse(list, i*k, (i+1)*k-1);
    for (i=0; i<cnt-1; i++) list[i].next=list[i+1].addr;
    list[cnt-1].next=-1;

    for (i=0; i<cnt; i++) {
        printf("%05d %d ", list[i].addr, list[i].key);
        if (list[i].next==-1) printf("-1");//要对-1做处理
        else printf("%05d\n", list[i].next);
    }
}

//1、注意只要能组成k个数据就翻转一次，我之前没注意只翻转一次，结果有两个用例不过
//代码看了n遍也没发现错，审题还是要注意啊
//2、如果只翻转一次先对next赋值再翻转也没什么，翻转多次的话还是先翻转再赋值
//3、注意可能有不在一条链表上的数据，要舍弃
//4、对-1座处理
int main(int argc, char *argv[])
{
   fun1();
}

