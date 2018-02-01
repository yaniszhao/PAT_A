#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001

typedef struct {
    int addr;
    int key;
    int next;
    int flag;
} Node;

int cmp(const void *a, const void *b)
{
    Node *x=(Node *)a;
    Node *y=(Node *)b;
    return x->key-y->key;
}

void fun1()
{
    int map[MAX]={0};
    Node recode[MAX];
    int n, st;
    int i,j;
    
    scanf("%d%d", &n, &st);
    for (i=1; i<=n; i++) {
        scanf("%d%d%d", &recode[i].addr, &recode[i].key, &recode[i].next);
        recode[i].flag=0;
        map[recode[i].addr]=i;
    }
    
    while (st!=-1) {
        recode[map[st]].flag=1;
        st=recode[map[st]].next;
    }
    
    for (i=1,j=1; i<=n;)//去掉不在链表中的结点
        if (recode[i].flag==1) recode[j++]=recode[i++];
        else i++;
    n=j-1;
    
    qsort(&recode[1], n, sizeof(recode[0]), cmp);
    for (i=1; i<=n; i++)
        recode[i].next=((i==n)?-1:recode[i+1].addr);
    
    if(n==0) printf("0 -1");
    else printf("%d %05d\n", n, recode[1].addr);
    for (i=1; i<=n; i++) {
        printf("%05d %d", recode[i].addr, recode[i].key);
        if (recode[i].next==-1) printf(" -1\n");
        else printf(" %05d\n", recode[i].next);
    }
}

//============================================================
int cmp2(const void *a, const void *b)
{
    Node *x=(Node *)a;
    Node *y=(Node *)b;
    if (x->flag==0) return 1;//只要不在链表中就放到后面
    return x->key-y->key;
}

void fun2()
{
    int map[MAX]={0};
    Node recode[MAX];
    int n, st;
    int i,j,cnt=0;
    
    scanf("%d%d", &n, &st);
    for (i=1; i<=n; i++) {
        scanf("%d%d%d", &recode[i].addr, &recode[i].key, &recode[i].next);
        recode[i].flag=0;
        map[recode[i].addr]=i;
    }
    
    while (st!=-1) {
        recode[map[st]].flag=1;
        st=recode[map[st]].next;
        cnt++;
    }

    qsort(&recode[1], n, sizeof(recode[0]), cmp2);
    for (i=1; i<=cnt; i++)
        recode[i].next=((i==cnt)?-1:recode[i+1].addr);
    
    if(cnt==0) printf("0 -1");
    else printf("%d %05d\n", cnt, recode[1].addr);
    for (i=1; i<=cnt; i++) {
        printf("%05d %d", recode[i].addr, recode[i].key);
        if (recode[i].next==-1) printf(" -1\n");
        else printf(" %05d\n", recode[i].next);
    }
}

//1、处理有的结点不在一条链表中，可以删除(fun1)，也可以排序的时候放在最后(fun2)，否则有用例不过
//2、当n==0的时候输出0 -1，否则最后一个用例不过
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}

