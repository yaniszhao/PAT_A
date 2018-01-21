#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30000
typedef long long LLONG;

typedef struct stStu {
    LLONG id;
    int score;
    int loc;
} Stu;

void SortScore(int arr[], int n)
{//排序要从大到小排，不是从小到大
    int i,j,max,t;
    for (i=0; i<n-1; i++) {
        max=i;
        for (j=i+1; j<n; j++) {
            if (arr[j]>arr[max]) max=j;
        }
        t=arr[i];
        arr[i]=arr[max];
        arr[max]=t;
    }
}


void SortStu(Stu arr[], int n)
{//排序要从大到小排，不是从小到大
    int i,j,max;
    Stu t;
    for (i=0; i<n-1; i++) {
        max=i;
        for (j=i+1; j<n; j++) {//排名相同时，id小的在前
            if (arr[j].score>arr[max].score)
                max=j;
            else if (arr[j].score==arr[max].score)
                if (arr[j].id<arr[max].id) max=j;
        }
        memcpy(&t, &arr[i], sizeof(t));
        memcpy(&arr[i], &arr[max], sizeof(t));
        memcpy(&arr[max], &t, sizeof(t));
//        t.id=arr[i].id; t.score=arr[i].score; t.loc=arr[i].loc;
//        arr[i].id=arr[max].id; arr[i].score=arr[max].score; arr[i].loc=arr[max].loc;
//        arr[max].id=t.id; arr[max].score=t.score; arr[max].loc=t.loc;
    }
}

int GetRank(int scores[], int score, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (scores[i]==score)
            return i+1;
    return -1;
}

void fun1()
{
    Stu stu[MAX];
    int scores[MAX];
    int *loc_score[MAX];
    int knum[MAX];
    int n,k;
    int i,j,cnt=0;
    
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &k);
        knum[i]=k;
        loc_score[i]=(int *)malloc(k*sizeof(*loc_score[0]));
        for (j=0; j<k; j++) {
            scanf("%lld%d", &stu[cnt].id, &stu[cnt].score);
            stu[cnt].loc=i+1;//用的时候注意减一
            scores[cnt]=stu[cnt].score;
            loc_score[i][j]=stu[cnt].score;
            cnt++;
        }
        SortScore(loc_score[i], knum[i]);
    }
    
    SortStu(stu, cnt);
    SortScore(scores, cnt);
    
    printf("%d\n", cnt);
    for (i=0; i<cnt; i++) {//注意stu.loc使用要减一
        printf("%lld %d %d %d\n", stu[i].id, \
               GetRank(scores, stu[i].score, cnt), \
               stu[i].loc, \
               GetRank(loc_score[stu[i].loc-1], stu[i].score, knum[stu[i].loc-1]));
    }

}
//=========================================================
typedef struct stStu2 {
    LLONG id;
    int score;
    int loc;
    int rank;
    int loc_rank;
} Stu2;

void SortStu2(Stu2 arr[], int n)
{//排序要从大到小排，不是从小到大
    int i,j,max;
    Stu2 t;
    for (i=0; i<n-1; i++) {
        max=i;
        for (j=i+1; j<n; j++) {//排名相同时，id小的在前
            if (arr[j].score>arr[max].score)
                max=j;
            else if (arr[j].score==arr[max].score)
                if (arr[j].id<arr[max].id) max=j;
        }
        if (max==i) continue;
        memcpy(&t, &arr[i], sizeof(t));
        memcpy(&arr[i], &arr[max], sizeof(t));
        memcpy(&arr[max], &t, sizeof(t));
    }
}

void SortInsertStu2(Stu2 arr[], int n)
{//排序要从大到小排，不是从小到大
    int i,j,max;
    Stu2 t;
    for (i=1; i<n; i++) {
        max=i;
        memcpy(&t, &arr[i], sizeof(t));
        for (j=i-1; j>=0; j--) {//排名相同时，id小的在前
            if (arr[j].score<t.score || (arr[j].score==t.score && arr[j].id>t.id))
                memcpy(&arr[j+1], &arr[j], sizeof(t));
            else
                break;
        }
        memcpy(&arr[j+1], &t, sizeof(t));
    }
}

int Pivot(Stu2 arr[], int n)
{
    int i=0,j=n-1;
    Stu2 t;
    memcpy(&t, &arr[0], sizeof(t));
    while (i<j) {
        while(i<j) {
            if (arr[j].score>t.score || (arr[j].score==t.score && arr[j].id<t.id)) {
                memcpy(&arr[i], &arr[j], sizeof(t));
                i++;
                break;
            }
            else
                j--;
        }
        
        while(i<j) {
            if (arr[i].score<t.score || (arr[i].score==t.score && arr[i].id>t.id)) {
                memcpy(&arr[j], &arr[i], sizeof(t));
                j--;
                break;
            }
            else
                i++;
        }
    }
    memcpy(&arr[i], &t, sizeof(t));
    return i;
}

void SortQuickStu2(Stu2 arr[], int n)
{//排序要从大到小排，不是从小到大
    if (n<=0) return;
    int pivot=Pivot(arr, n);
    SortQuickStu2(arr, pivot);
    SortQuickStu2(&arr[pivot+1], n-pivot-1);
}

void fun2()
{
    Stu2 stu[MAX];
    int n,k;
    int i,j,cnt=0;
    int start, end;
    
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &k);
        for (j=0; j<k; j++) {
            scanf("%lld%d", &stu[cnt].id, &stu[cnt].score);
            stu[cnt].loc=i+1;//用的时候注意减一
            cnt++;
        }
        
        start=cnt-k; end=cnt;
        SortQuickStu2(&stu[start], k);
        for (j=start; j<end; j++) {
            if (j==start)
                stu[start].loc_rank=1;
            else
                stu[j].loc_rank = (stu[j].score==stu[j-1].score) ? stu[j-1].loc_rank : j-start+1;
        }
    }
    
    SortQuickStu2(stu, cnt);
    
    printf("%d\n", cnt);
    for (i=0; i<cnt; i++) {//注意stu.loc使用要减一
        if (i==0)
            stu[i].rank=1;
        else
            stu[i].rank = (stu[i].score==stu[i-1].score) ? stu[i-1].rank : i+1;

        printf("%013lld %d %d %d\n", stu[i].id, stu[i].rank, stu[i].loc, stu[i].loc_rank);
    }
    
}

//相同成绩，id小的在前
//数据大了会超时，用stl的sort试试，用第一种排名方法stl也还会超时，要用第二种
//用c改了排名算法和用快排才能避免超时，选择排序和插入排序都会超时
//输出学号的时候要13位格式输出，否则最后一个用例不超时但会错误
int main(int argc, char *argv[])
{
    //fun1();//最后一个用例排序超时了
    fun2();
}
