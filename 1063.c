#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10001
#define MAXSET 50

int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

int SortAndUniq(int arr[], int n)
{
    int i,j;
    qsort(&arr[1], n, sizeof(arr[0]), cmp);
    for (i=1,j=1; i<=n;)//去重
        if (arr[i]==arr[j]) i++;
        else arr[++j]=arr[i++];
    arr[0]=1;//已排序和去重
    return j;
}

void fun1()
{
    int *set[MAXSET];
    int cnt[MAXSET]={0};
    int n,m,k;
    int i,j,a,b;
    int ncom,ncnt;

    scanf("%d", &n);
    for (i=0; i<n; i++) {//记录数据
        set[i]=(int *)malloc(MAX*sizeof(set[0][0]));
        scanf("%d", &m);
        cnt[i]=m;
        set[i][0]=0;//还没排序和去重
        for (j=1; j<=m; j++)
            scanf("%d", &set[i][j]);
    }

    scanf("%d", &k);
    for (m=0; m<k; m++) {//用m是因为后面i、j一起用好看点，就没用i,而且m正好没用
        scanf("%d%d", &a, &b);
        a--; b--;//得到下标
        if (set[a][0]==0) cnt[a]=SortAndUniq(set[a], cnt[a]);
        if (set[b][0]==0) cnt[b]=SortAndUniq(set[b], cnt[b]);
        ncom=0; ncnt=0;
        for (i=1,j=1; i<=cnt[a]&&j<=cnt[b];) {//最关键的就是这个地方
            if (set[a][i]==set[b][j]) {//相同两个都往后走
                ncom++; ncnt++;
                i++; j++;
            }
            else {//不相同小的往后走
                ncnt++;
                if (set[a][i]<set[b][j]) i++;
                else j++;
            }
        }
        //注意是<=不是<;而且cnt[]-i后要+1
        //下面两个最多if只有一个是true
        if (i<=cnt[a]) ncnt+=cnt[a]-i+1;
        if (j<=cnt[b]) ncnt+=cnt[b]-j+1;
        printf("%.1f%%\n", ((float)ncom*100)/ncnt);//100乘在里面比乘在最后好点
    }
}

void fun2()
{//用stl的set可以省去不少麻烦，天生适合这种题

}

//1、这道题还是要点技巧的，虽然一次就AC了
//要排序和去重，为了不重复操作set[][0]号位置标识是否已排序去重
//去重操作也挺经典的，不要忘了
//最重要的就是统计相同值个数和总共个数，注意里面的细节
//2、用stl的set来做可省去排序和去重
int main(int argc, char *argv[])
{
   fun1();
}

