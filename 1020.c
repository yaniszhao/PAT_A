#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//10e9取二进制时，符号占最多空间也小于2e32即3G左右(2e10为1024)
#define MAXLEN 30

typedef struct stTree {
    int v;
    struct stTree *lchild;
    struct stTree *rchild;
} Tree;

Tree* CreatTree(int in[], int l1, int r1, int post[], int l2, int r2)
{
    Tree *p;
    int mid=0;
    if (l1>r1) return NULL;
    for (mid=l1; mid<=r1; mid++)
        if (in[mid]==post[r2]) break;
    p=(Tree *)malloc(sizeof(Tree));
    p->v=post[r2];
    p->lchild=CreatTree(in, l1, mid-1, post, l2, l2+mid-l1-1);
    p->rchild=CreatTree(in, mid+1, r1, post, l2+mid-l1, r2-1);
    return p;
}

void LevelSearch(int lev[], Tree *root)
{
    Tree* que[MAXLEN];
    Tree* p;
    int head=0, tail=0;
    int i=0;
    que[tail++]=root;
    while (head!=tail) {
        p=que[head++];
        lev[i++]=p->v;
        if (p->lchild) que[tail++]=p->lchild;
        if (p->rchild) que[tail++]=p->rchild;
    }
}

void fun1()
{
    int postorder[MAXLEN];
    int inorder[MAXLEN];
    int levorder[MAXLEN];
    int n;
    int i;
    Tree *root;
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &postorder[i]);
    for (i=0; i<n; i++)
        scanf("%d", &inorder[i]);
    root=CreatTree(inorder, 0, n-1, postorder, 0, n-1);
    LevelSearch(levorder, root);
    printf("%d", levorder[0]);
    for (i=1; i<n; i++)
        printf(" %d", levorder[i]);
}
//================================================================
typedef struct stNode {
    int inleft;
    int inright;
    int postleft;
    int postright;
} Node;

void fun2()
{//最后一个用例过不了
    int postorder[MAXLEN];
    int inorder[MAXLEN];
    int levorder[MAXLEN];
    int n;
    Node *que[MAXLEN], *tmp, *p;
    int i, head=0, tail=0;
    int l1,r1,l2,r2, mid;
    
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &postorder[i]);
    for (i=0; i<n; i++)
        scanf("%d", &inorder[i]);
    
    tmp=(Node *)malloc(sizeof(*tmp));
    tmp->inleft=0; tmp->inright=n-1;
    tmp->postleft=0; tmp->postright=n-1;
    que[tail++]=tmp;
    i=0;
    while (head!=tail) {
        tmp=que[head++];
        l1=tmp->inleft; r1=tmp->inright;
        l2=tmp->postleft; r2=tmp->postright;
        
        for (mid=l1; mid<=r2; mid++)
            if (inorder[mid]==postorder[r2]) break;
        
        levorder[i++]=postorder[r2];
        
        if (mid-1>=l1) {
            p=(Node *)malloc(sizeof(*p));
            p->inleft=l1; p->inright=mid-1;
            p->postleft=l2; p->postright=l2+mid-l1-1;
            que[tail++]=p;
        }
        
        if (mid+1<=r1) {
            p=(Node *)malloc(sizeof(*p));
            p->inleft=mid+1; p->inright=r1;
            p->postleft=l2+mid-l1; p->postright=r2-1;
            que[tail++]=p;
        }
        
        free(tmp);
    }
    
    printf("%d", levorder[0]);
    for (i=1; i<n; i++)
        printf(" %d", levorder[i]);
}
//================================================================

void CountLevelSearch(int lev[], int in[], int l1, int r1, int post[], int l2, int r2)
{
    static int cnt=0;
    int mid;
    if (l1>r2) return;
    for (mid=l1; mid<=r2; mid++)
        if (in[mid]==post[r2]) break;
    lev[cnt++]=post[r2];
    CountLevelSearch(lev, in, l1, mid-1, post, l2, l2+mid-l1-1);
    CountLevelSearch(lev, in, mid+1, r1, post, l2+mid-l1, r2-1);
}

void fun3()
{//不能用递归算法，因为每一个结点会递归下去，不是按层走，所以这个方法不行
    int postorder[MAXLEN];
    int inorder[MAXLEN];
    int levorder[MAXLEN];
    int n;
    int i;
    
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &postorder[i]);
    for (i=0; i<n; i++)
        scanf("%d", &inorder[i]);
    
    CountLevelSearch(levorder, inorder, 0, n-1, postorder, 0, n-1);
    
    printf("%d", levorder[0]);
    for (i=1; i<n; i++)
        printf(" %d", levorder[i]);
}

//================================================================

void GetTreeValue(int lev[], int idx, int in[], int l1, int r1, int post[], int l2, int r2)
{//递归确定顺序表存储二叉树中值的位置
    int mid;
    if (l1>r1) return;
    for (mid=l1; mid<r1; mid++)
        if (in[mid]==post[r2]) break;
    lev[idx]=post[r2];
    GetTreeValue(lev, 2*idx, in, l1, mid-1, post, l2, l2+mid-l1-1);
    GetTreeValue(lev, 2*idx+1, in, mid+1, r1, post, l2+mid-l1, r2-1);
}

void fun4()
{//不能用递归算法，因为每一个结点会递归下去，不是按层走
    int postorder[MAXLEN];
    int inorder[MAXLEN];
    //当每一层只有一个结点的时候空间最多，此时值为2^MAXLEN-1,从一号位置开始，则刚好
    //2^MAXLEN-1用2<<MAXLEN表示好像不行，所以还是直接用数表示，2^10是1024
//#define MAXTREELEN (1024*1024*1024)
    //取上面个值内存会超限，取一个相对大的值吧，题目给的最大内存为2^26个自己，所以这里取2^20
    #define MAXTREELEN (1024*1024)
    int *lev;//直接用数组，可能栈不够，所以用动态数组
    int n;
    int i, cnt=0;
    
    lev=(int *)malloc(MAXTREELEN*(sizeof(*lev)));//free不free无所谓了
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &postorder[i]);
    for (i=0; i<n; i++)
        scanf("%d", &inorder[i]);
    
    for (i=1; i<MAXTREELEN; i++)
        lev[i]=-1;
    //1号位开始
    GetTreeValue(lev, 1, inorder, 0, n-1, postorder, 0, n-1);
    
    for (i=1; i<MAXTREELEN; i++) {
        if (lev[i]!=-1) {
            if (cnt==0) printf("%d", lev[i]);
            else printf(" %d", lev[i]);
            cnt++;
        }
    }
}

int main(int argc, char *argv[])
{
    //fun1();
    //fun2();
    //fun3();
    fun4();
}
