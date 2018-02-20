#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int key;
    int hei;
    struct node *lch;
    struct node *rch;
} Node;

int GetHeight(Node *p)
{
    return p==NULL?0:p->hei;
}

int Max(Node *p1, Node *p2)
{
    int hei1=GetHeight(p1);
    int hei2=GetHeight(p2);
    return hei1>hei2?hei1:hei2;
}

void RotateL(Node **p)
{
    Node *root=*p;
    Node *rch=root->rch;
    root->rch=rch->lch;
    rch->lch=root;
    *p=rch;
    //得到root和rch的高度；父节点的高度在选择完后会自己调整
    root->hei = Max(root->lch, root->rch) + 1;
    rch->hei = Max(rch->lch, rch->rch) + 1;
}

void RotateR(Node **p)
{
    Node *root=*p;
    Node *lch=root->lch;
    root->lch=lch->rch;
    lch->rch=root;
    *p=lch;
    //得到root和lch的高度；父节点的高度在选择完后会自己调整
    root->hei = Max(root->lch, root->rch) + 1;
    lch->hei = Max(lch->lch, lch->rch) + 1;
}

int Insert(Node **p, int key)
{
    Node *root=*p;
    if (root==NULL) {
        *p=root=(Node*)malloc(sizeof(Node));
        root->key=key;
        root->hei=1;
        root->lch=root->rch=NULL;
    }
    else {
        if (key==root->key) return -1;//重复值
        else if (key>root->key) {//key大
            if (Insert(&root->rch, key)==-1) return -1;//重复值
            root->hei = Max(root->lch, root->rch) + 1;
            //调整平衡，插的右边，只可能右边大
            if (GetHeight(root->rch)-GetHeight(root->lch)>1) {
                if (key>root->rch->key) {//右右
                    RotateL(p);
                }
                else {//右左
                    RotateR(&root->rch);
                    root->hei = Max(root->lch, root->rch) + 1;
                    RotateL(p);
                }
            }
        }
        else {//key小
            if (Insert(&root->lch, key)==-1) return -1;//重复值
            root->hei = Max(root->lch, root->rch) + 1;
            //调整平衡，插的左边，只可能左边大
            if (GetHeight(root->lch)-GetHeight(root->rch)>1) {
                if (key<root->lch->key) {//左左
                    RotateR(p);
                }
                else {//左右
                    RotateL(&root->lch);
                    root->hei = Max(root->lch, root->rch) + 1;
                    RotateR(p);
                }
            }
        }
    }
    return 0;
}

void fun1()
{
    Node *root=NULL;
    int n;
    int i, key;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &key);
        Insert(&root, key);
    }
    printf("%d", root->key);
}

//1、第一次写AVL有点生硬，后面可以多熟悉下，这里只是插入还不涉及删除要简单很多
//2、每次插入之后和对孩子做过旋转要更新自己的高度，容易遗漏
//3、这里数据少，可以不用存高度，每次递归获得，可以少写很多代码尤其是更新高度的代码
int main(int argc, char *argv[])
{
   fun1();
}

