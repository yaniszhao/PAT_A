#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 10000
#define MAXM 100

int arr[MAXN];
int coins[MAXN], cnt=0;
int n,m;

int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

int Dp(int u, int val)
{
    if (u>=n) return 0;
    if (arr[u]>val||val==0) return 0;//Dp(u+1, val);
    //if (arr[u]==val) return val;
    //已经从小到大排序了，所以小的优先选
    if (arr[u]+Dp(u+1, val-arr[u])==val) {
        coins[cnt++]=arr[u];
        return val;
    }
    else if (Dp(u+1, val)==val)
        return val;
    return 0;
}

void fun1()
{//递归，最后一个用例超时
    int i,ans;
    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(arr[0]), cmp);
    ans=Dp(0, m);
    if (ans!=m) printf("No Solution");
    else {
        printf("%d", coins[cnt-1]);
        for (i=cnt-2; i>=0; i--)
            printf(" %d", coins[i]);
    }
}
//============================================

void Dp2(int dp[])
{
    int i,j;
    dp[0]=1;//0都是可以的，就是不选
    for (j=m; j>0; j--)//第一次赋值
        dp[j]=arr[n-1]==j?1:0;
    //确认每一个数和前面的数能组成1~m中的哪些值
    for (i=n-2; i>=0; i--)//从大到小，从小到大应该也可以
        for (j=m; j>0; j--)//我这是逆向赋值，正向应该也可以
            dp[j]=(dp[j]==1||dp[j-arr[i]]==1)?1:0;
}

void fun2()
{//这个函数只能确定能还是不能，不能确定由哪些组成
    int dp[MAXM+1];
    int i,ans;
    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(arr[0]), cmp);
    Dp2(dp);
    printf("%d", dp[m]);
}
//============================================

//void Dp3(int dp[][MAXM+1])
//{//从小到大处理，但是这道题要从小到大选，只能从大到小处理
//    int i,j;
//    for (i=0; i<n; i++) dp[i][0]=1;//0都是可以的，就是不选
//    for (j=1; j<=m; j++)//第一次赋值
//        dp[0][j]=arr[0]==j?1:0;
//    //确认每一个数和前面的数能组成1~m中的哪些值
//    for (i=1; i<n-1; i++)//从小到大
//        for (j=1; j<=m; j++)//正向赋值
//            dp[i][j]=(dp[i-1][j]||dp[i-1][j-arr[i]])?1:0;
//}

void Dp3(int dp[][MAXM+1])
{//这道题要从小到大选，只能从大到小处理
    int i,j;
    for (i=0; i<n; i++) dp[i][0]=1;//0都是可以的，就是不选
    for (j=1; j<=m; j++)//第一次赋值
        dp[n-1][j]=arr[n-1]==j?1:0;
    //确认每一个数和前面的数能组成1~m中的哪些值
    for (i=n-2; i>=0; i--)//从大道小
        for (j=1; j<=m; j++)//正向赋值
            if (j<arr[i])  dp[i][j]=0;//不加有2个用例不过
            else dp[i][j]=(dp[i+1][j]||dp[i+1][j-arr[i]])?1:0;
}

void fun3()
{
    int dp[MAXN][MAXM+1];
    int i,ans;
    scanf("%d%d", &n, &m);
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(arr[0]), cmp);
    Dp3(dp);
    ans=dp[0][m];
    if (ans==0) printf("No Solution");
    else {
        for (i=0; i<n&&m>0; i++) {//m>=arr[i]是肯定的
            //注意i==n-1的情形，这题数组下标越界的问题我犯了2次
            if (i==n-1 || dp[i+1][m-arr[i]]==1) {
                if (cnt==0) printf("%d", arr[i]);
                else printf(" %d", arr[i]);
                cnt++;
                m=m-arr[i];
            }
        }
    }
}

//1、动态规划最容易做的是递归，如果递归超时考虑非递归方法
//2、非递归放法存储空间有n^2和n两种，如果只是问可不可行则用n的那种好点，因为省空间
//3、但这道题要求所有相关点，只能用n^2的空间记录没个点的信息
//4、每一行的信息是包含和递归下结点的共同结果，而只是当前结点的信息，所以先后次序有有关系
//5、注意判断数组越界，这道题我忘了两个地方，导致3个用例不过，花了很多时间；
//6、所以递归的边界判断和数组的边界判断都重要
int main(int argc, char *argv[])
{
   fun3();
}

