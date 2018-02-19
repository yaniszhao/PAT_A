#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
} Node;

int l[MAX],r[MAX];
int arr[MAX];

int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

Node *CreateTree(int idx)
{
    Node *root;
    if (idx==-1) return NULL;
    root=(Node*)malloc(sizeof(Node));
    root->left=CreateTree(l[idx]);
    root->right=CreateTree(r[idx]);
    return root;
}

void LDR(Node *root)
{
    static int cnt=0;
    if (!root) return;
    LDR(root->left);
    root->key=arr[cnt++];
    LDR(root->right);
}

void LevelPrint(Node *root)
{
    Node *que[MAX];
    int head=0, tail=0;
    que[tail++]=root;
    while (head!=tail) {
        root=que[head++];
        if (head==1) printf("%d", root->key);
        else printf(" %d", root->key);
        if (root->left) que[tail++]=root->left;
        if (root->right) que[tail++]=root->right;
    }
}

void fun1()
{
    Node *root;
    int n;
    int i;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d%d", &l[i], &r[i]);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(arr[0]), cmp);
    root=CreateTree(0);//先把树形建好
    LDR(root);//中序把数据填进去
    LevelPrint(root);//层序遍历
}

//1、树形不是完全二叉树，不能像原来那样做，最好就是先建树再赋值，最后再层序
//2、树结点的左右孩子可以用int来存下标，参考liuchuo代码；思路和我的是一样的
int main(int argc, char *argv[])
{
   fun1();
}

