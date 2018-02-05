#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1001



int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

void CreateTree(int tree[], int pos, int in[], int st, int ed)
{
    int n,dep,rest;
    int left,mid;

    if (st>ed) return;//开始写反了第一个就返回了

    n=ed-st+1;
    for  (dep=1; n>((1<<dep)-1); dep++);//得到高度

    //注意dep为1和2要分开讨论，因为会导致1<<右边为负数
    //用pow函数好像就不用分开讨论了
    if (dep==1) mid=st;
    else if (dep==2) mid=st+1;
    else {
        rest=(1<<dep)-1-n;//最后一层右边空多少

        if (rest==0) rest=(1<<dep-1);//满了
        else rest=(1<<dep-1)-rest;//最后一层从左到右有多少元素

        if (rest <= 1<<dep-2) left=rest;//右边没元素
        else left=(1<<dep-2);//右边有元素
        //left=log(n + 1)/log(2);//left好像可以直接由这个得到
        mid=st+(1<<dep-2)+left-1;
    }
    tree[pos]=in[mid];
    CreateTree(tree, 2*pos, in, st, mid-1);
    CreateTree(tree, 2*pos+1, in, mid+1, ed);
}

void fun1()
{
    int in[MAX];
    int tree[MAX];
    int n;
    int i,first=1;
    //全部初始化-1，因为-1为全F比如四位的0xFFFFFFFF
    memset(tree, 0xFF, MAX*sizeof(tree[0]));
    scanf("%d", &n);
    for (i=1; i<=n; i++) scanf("%d", &in[i]);
    qsort(&in[1], n, sizeof(in[0]), cmp);//排序得到中序
    CreateTree(tree, 1, in, 1, n);
    for (i=1; i<=MAX; i++)
        if (tree[i]!=-1)
            if (first) {printf("%d", tree[i]); first=0;}
            else printf(" %d", tree[i]);
//    for (i=1; i<=n; i++)//因为是完全二叉树，中间不会有空的
//        if (first) {printf("%d", tree[i]); first=0;}
//        else printf(" %d", tree[i]);
}

//1、这道题和之前的一题很像，都是构造顺序树，然后顺序遍历就是层序遍历
//非链表的层序遍历感觉都可以用这种讨论，只是多花了一些空间
//2、在递归函数处要注意出口，别写反了，还有dep为1和2的时候要单独做处理
//3、肯定可以构造链式树来做，但是太麻烦了
int main(int argc, char *argv[])
{
   fun1();
}

