#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int cmp1(const void*a, const void*b)
{//从小到大
    return (*(int*)a)>(*(int *)b);
}

int cmp2(const void*a, const void*b)
{//从大到小，有reverse就不用这个了
    return (*(int*)a)<(*(int *)b);
}

//int IsBST(int pre[], int l1, int r1, int in[], int l2, int r2)
//{
//    int mid=(l2+r2)/2;
//    if (l1>r1) return 1;
//    if (pre[l1]!=in[mid]) return 0;
//    if (IsBST(pre, l1+1, l1+mid-l2, in, l2, mid-1)==0)
//        return 0;
//    if (IsBST(pre, l1+mid-l2+1, r1, in, mid+1, r2)==0)
//        return 0;
//    return 1;
//}

int IsBST(int pre[], int in[], int n)
{
    int mid=0;
    if (n==0) return 1;
    
    for (mid=0; in[mid]!=pre[0] && mid<n; mid++);
    if (mid==n) return 0;//当假设的中序和前序不符合时返回错误

    if (IsBST(&pre[1], in, mid)==0)
        return 0;
    if (IsBST(&pre[1+mid], &in[mid+1], n-mid-1)==0)
        return 0;
    return 1;
}

void Reverse(int arr[], int n)
{//镜像直接reverse不用再排序了
    int i, t;
    for (i=0; i<=(n-1)/2; i++) {
        t=arr[i];
        arr[i]=arr[n-1-i];
        arr[n-1-i]=t;
    }
}

void PreToPost(int pre[], int post[], int n)
{//如果是完全二叉树用这个应该可以
    int len=(n-1)/2;
    if (n<=0) return;
    post[n-1]=pre[0];
    PreToPost(&pre[1], post, len);
    PreToPost(&pre[len+1], &post[len], len);
}

void PreAndInToPost(int pre[], int in[], int post[], int n, int flag)
{//因为中序和前序满足了所有一定会找到mid不用做判断
    int mid=0;
    if (n<=0) return;
    if (flag==1)//有相同值时从大到小和从小到大mid作位根的位置不一样
        for (mid=0; in[mid]!=pre[0] && mid<n; mid++);
    else if (flag==2)
        for (mid=n-1; in[mid]!=pre[0] && mid>=0; mid--);
    post[n-1]=pre[0];
    PreAndInToPost(&pre[1], in, post, mid, flag);
    PreAndInToPost(&pre[1+mid], &in[mid+1], &post[mid], n-mid-1, flag);
}

void fun1()
{
    int pre[MAX];
    int in[MAX];
    int post[MAX];
    int n;
    int i, flag=0;
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &pre[i]);
    memcpy(in, pre, n*sizeof(pre[0]));
    qsort(in, n, sizeof(in[0]), cmp1);
    if (IsBST(pre, in, n))
        flag=1;
    else {
        Reverse(in, n);
        if (IsBST(pre, in, n))
            flag=2;
    }
    
    if (flag==0)
        printf("NO");
    else {
        //PreToPost(pre, post, n);
        PreAndInToPost(pre, in, post, n, flag);
        printf("YES\n");
        printf("%d", post[0]);
        for (i=1; i<n; i++)
            printf(" %d", post[i]);
    }
}

void fun2()
{//根据输入顺序建BST树来做
    
}

//这题的输入是给的BST插入顺序，问的是这个插入顺序是否是BST或其镜像的前序（先确定是BST然后判断输入顺序是前序）
//我一开始以为就是前序，然后判断能否构成BST或其镜像
//虽然理解反了（先确定是前序然后判断能否是BST），但是原理是一样的：BST和给定前序是否统一
//1、BST的中序一定是按大小排列的
//2、可能不是完全二叉树，前面假设是完全二叉树有几个用例不过
//3、相同值从小到达左边个一定是根，因为右节点>=根节点；从大到小反之
int main(int argc, char *argv[])
{
    fun1();
}
