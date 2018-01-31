#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000


//1、当前元素前面比当前值小出来的个数要大于（当前值-m）
//2、判断在后面的但值比当前小的是否逆序
void fun1()
{
    int map[MAX];//存下标
    int arr[MAX];
    int m,n,k;
    int i,j,t;
    int pre, flag;
    
    scanf("%d%d%d", &m, &n, &k);
    for (i=0; i<k; i++) {
        pre=0; flag=1;
        for (j=0; j<n; j++) {
            scanf("%d", &arr[j]);
            map[arr[j]]=i;
        }
        for (j=0; j<n; j++) {
            for (t=0; t<j; t++) if (arr[t]<arr[j]) pre++;
            if (arr[j]-pre>m) {flag=0; break;}
            //判断在后面的但值比当前小的是否逆序...
        }
        if (flag==0) printf("NO\n");
        else printf("YES\n");
    }
}

//=====================================================

void fun2()
{
    int arr[MAX][MAX];
    int que[MAX],top;
    int m,n,k;
    int i,j,t;
    int flag;
    scanf("%d%d%d", &m, &n, &k);
    for (i=0; i<k; i++)
        for (j=0; j<n; j++)
            scanf("%d", &arr[i][j]);
    
    for (i=0; i<k; i++) {
        flag=1; top=-1;
        for (t=1,j=0; t<=n; t++) {
            if (top+1==m) {flag=0; break;}
            que[++top]=t;
            //top和j要加限制，否则第一个用例过不了
            while (top>-1 && j<n && arr[i][j]==que[top]) {top--; j++;}
        }
        if (j!=n) flag=0;
        
        if (flag==0) printf("NO\n");
        else printf("YES\n");
    }
}

//直接用栈模拟就可以了
//第一种方法感觉很麻烦而且不一定
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}

