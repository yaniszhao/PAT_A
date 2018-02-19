#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000
#define MAXVAL 10000

typedef struct {
    int addr;
    int val;
    int next;
} Node;

void fun1()
{//尾插两个用例会超时
    Node map[MAX];
    char mapval[MAXVAL]={0};
    int start, n;
    int addr, val, next;
    int i, pre, tmp, rlist=-1;
    scanf("%d%d", &start, &n);
    for (i=0; i<n; i++) {
        scanf("%d%d%d", &addr, &val, &next);
        map[addr].val=val;
        map[addr].next=next;
    }
    for (pre=start, addr=map[start].next; addr!=-1; ) {
        if (mapval[abs(map[addr].val)]==1) {//绝对值已经存在了
            map[pre].next=map[addr].next;//断掉当前节点
            //插入到remove list；尾插，插入麻烦，打印方便；头插，插入简单，打印麻烦
            if (rlist==-1) {
                map[addr].next=-1;
                rlist=addr;
            }
            else {
                for (tmp=rlist; map[tmp].next!=-1; tmp=map[tmp].next);
                map[addr].next=-1;
                map[tmp].next=addr;
            }
            addr=map[pre].next;
        }
        else {
            mapval[abs(map[addr].val)]=1;
            pre=addr;//要处理pre
            addr=map[addr].next;
        }
    }
    for (addr=start; addr!=-1; addr=map[addr].next)
        if (map[addr].next==-1) printf("%05d %d -1\n", addr, map[addr].val);
        else printf("%05d %d %05d\n", addr, map[addr].val, map[addr].next);
    for (addr=rlist; addr!=-1; addr=map[addr].next)
        if (map[addr].next==-1) printf("%05d %d -1\n", addr, map[addr].val);
        else printf("%05d %d %05d\n", addr, map[addr].val, map[addr].next);
}

void fun2()
{
    Node map[MAX];
    Node rlist[MAX];//removed list
    int rcnt=0;
    char mapval[MAXVAL]={0};
    int start, n;
    int addr, val, next;
    int i, pre;

    scanf("%d%d", &start, &n);
    for (i=0; i<n; i++) {
        scanf("%d%d%d", &addr, &val, &next);
        map[addr].addr=addr;
        map[addr].val=val;
        map[addr].next=next;
    }

//    if (start==-1) {
//        printf("-1\n-1\n");
//        return;
//    }

    mapval[abs(map[start].val)]=1;//这句不加，三个用例不过
    pre=start;
    for (addr=map[start].next; addr!=-1; ) {
        if (mapval[abs(map[addr].val)]==1) {//绝对值已经存在了
            if (rcnt!=0) rlist[rcnt-1].next=addr;
            rlist[rcnt].addr=addr;
            rlist[rcnt].val=map[addr].val;
            rlist[rcnt].next=-1;
            rcnt++;
            //准备处理下一个
            map[pre].next=map[addr].next;
            addr=map[pre].next;
        }
        else {
            mapval[abs(map[addr].val)]=1;
            pre=addr;//要处理pre
            addr=map[addr].next;
        }
    }

    for (addr=start; addr!=-1; addr=map[addr].next)
        if (map[addr].next==-1) printf("%05d %d -1\n", addr, map[addr].val);
        else printf("%05d %d %05d\n", addr, map[addr].val, map[addr].next);
    for (i=0; i<rcnt; i++)
        if (rlist[i].next==-1) printf("%05d %d -1\n", rlist[i].addr, rlist[i].val);
        else printf("%05d %d %05d\n", rlist[i].addr, rlist[i].val, rlist[i].next);
}

//1、用常规的尾插会超时，可以加一个尾指针；头插的话打印很不方便，不建议
//我这里是用的一个数组来存，其实没必要，就在fun1的基础上加尾指针应该就可以解决了
//2、循环从第1个开始的不是从第0个，一开始0初始化没做好，导致3个用例不过花了点时间才发现
//3、注意-1的处理，start为-1的用例好像没有，处理不处理无所谓
int main(int argc, char *argv[])
{
   fun2();
}

