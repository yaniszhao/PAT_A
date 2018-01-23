#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct stWord {
    int addr;
    char word;
    int nextaddr;
} Word;

int GetIndexFromArr(Word arr[], int n, int addr)
{//用这个好像不行，因为会出现2个相同的nextarr，这里返回只能返回一个下标
    int i;
    for (i=0; i<n; i++)
        if (arr[i].addr==addr) return i;
    return -1;
}

int GetNextAddrFromArr(Word arr[], int n, int addr)
{//还是返回地址好点
    int i;
    for (i=0; i<n; i++)
        if (arr[i].addr==addr) return arr[i].nextaddr;
    return -1;
}

void fun1()
{//最后一个用例会超时
    Word arr[MAX];
    int addr1, addr2, n;
    int i,j;
    scanf("%d %d %d", &addr1, &addr2, &n);
    for (i=0; i<n; i++)
        scanf("%d %c %d", &arr[i].addr, &arr[i].word, &arr[i].nextaddr);
    
    i=addr1;
    while (i!=-1) {
        j=addr2;
        while (j!=-1) {
            if (i==j) break;
            else j=GetNextAddrFromArr(arr, n, j);
        }
        if (i==j) break;
        else i=GetNextAddrFromArr(arr, n, i);
    }
    
    if (i!=-1) printf("%05d", i);
    else printf("-1");
}

//=========================================================

void fun2()
{//直接判断哪个地址出现了两次，但是有几个用例不过
    char arr[MAX]={0};
    int addr1, addr2, n;
    int i,j;
    char c,flag=0;
    int t1,t2;
    
    scanf("%d %d %d", &addr1, &addr2, &n);
    
    for (i=0; i<n; i++) {
        scanf("%d %c %d", &t1, &c, &t2);
        if (t2!=-1) arr[t2]++;
    }
    
    if (addr1==addr2) {
        printf("%05d", addr1);
        return;
    }
    
    for (i=0; i<MAX; i++)
        if (arr[i]==2) {printf("%05d", i); flag=1; break;}
    if (flag==0) printf("-1");
}

//=========================================================

int CountAddrNum(Word arr[], int n, int addr)
{//和fun2有类似的地方，还是用例不过，且还是会超时
    int num=0;
    int i;
    for (i=0; i<n; i++)
        if (arr[i].nextaddr==addr) num++;
    return num;
}

void fun3()
{
    Word arr[MAX];
    int addr1, addr2, n;
    int i,j;
    int flag=0;
    scanf("%d %d %d", &addr1, &addr2, &n);
    for (i=0; i<n; i++)
        scanf("%d %c %d", &arr[i].addr, &arr[i].word, &arr[i].nextaddr);
    for (i=0; i<n; i++)
        if (CountAddrNum(arr, n, arr[i].addr)==2) {printf("%05d", arr[i].addr); flag=1; break;}
    if (flag==0) printf("-1");
}

//=========================================================

int GetListLen(Word arr[], int n, int start)
{
    int len=0;
    while (start!=-1) {
        len++;
        start=GetNextAddrFromArr(arr, n, start);
    }
    return len;
}

void fun4()
{//这个是参照王道上的题，还是会超时，改成链表应该就可以
    Word arr[MAX];
    int addr1, addr2, n;
    int i,j;
    int len1, len2;
    
    scanf("%d %d %d", &addr1, &addr2, &n);
    for (i=0; i<n; i++)
        scanf("%d %c %d", &arr[i].addr, &arr[i].word, &arr[i].nextaddr);
    len1=GetListLen(arr, n, addr1);
    len2=GetListLen(arr, n, addr2);
    if (len1>len2)
        for (i=0; i<len1-len2; i++) addr1=GetNextAddrFromArr(arr, n, addr1);
    else
        for (i=0; i<len2-len1; i++) addr2=GetNextAddrFromArr(arr, n, addr2);
    
    while (addr1!=addr2) {
        addr1=GetNextAddrFromArr(arr, n, addr1);
        addr2=GetNextAddrFromArr(arr, n, addr2);
    }
    
    if (addr1!=-1) printf("%05d", addr1);
    else printf("-1");
}

//=========================================================

typedef struct stNode {
    char c;
    char visit;
    int next;
} Node;

void fun5()
{//参考别人的，和我的2、3两种方法类似，空间换时间，这个模拟了过程，我的比较死板
    Node arr[MAX];
    int addr1, addr2, n;
    int index;
    int i,j,flag=0;
    
    
    scanf("%d %d %d", &addr1, &addr2, &n);
    for (i=0; i<n; i++) {
        scanf("%d ", &index);
        scanf("%c %d", &arr[index].c, &arr[index].next);
        arr[index].visit=0;
    }
    while (addr1!=-1) {
        arr[addr1].visit=1;
        addr1=arr[addr1].next;
    }
    while (addr2!=-1) {
        if (arr[addr2].visit!=1) {
            arr[addr2].visit=1;
            addr2=arr[addr2].next;
        }
        else {
            printf("%05d", addr2);
            flag=1;
            break;
        }
    }
    if (flag==0) printf("-1");
}

int main(int argc, char *argv[])
{
    //fun1();
    //fun2();
    //fun3();
    //fun4();
    fun5();
}
