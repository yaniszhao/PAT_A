#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MAX 30000
typedef long long LLONG;

using namespace std;

typedef struct stStu {
    LLONG id;
    int score;
    int loc;
    int rank;
    int loc_rank;
} Stu;

bool cmp1(Stu a, Stu b)
{
    return a.score!=b.score ? a.score>b.score : a.id < b.id;
}

bool cmp2(int a, int b)
{
    return a>b;
}

int GetRank(vector<int> scores, int score, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (scores[i]==score)
            return i+1;
    return -1;
}

void fun1()
{
    vector<Stu> stu;
    Stu s;
    int n,k;
    int i,j;
    int start, end;
    
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &k);
        for (j=0; j<k; j++) {
            scanf("%lld%d", &s.id, &s.score);
            s.loc=i+1;//用的时候注意减一
            stu.push_back(s);
        }
        start=(int)stu.size()-k;end=(int)stu.size();
        sort(&stu[start], &stu[end], cmp1);
        stu[start].loc_rank=1;
        for (j=start+1; j<end; j++)
            stu[j].loc_rank = (stu[j].score==stu[j-1].score) ? stu[j-1].loc_rank : j-start+1;
    }
    
    sort(stu.begin(), stu.end(), cmp1);

    printf("%d\n", (int)stu.size());
    for (i=0; i<stu.size(); i++) {
        if (i==0)//和在外面做第一次处理的速度差不多的
            stu[i].rank=1;
        else
            stu[i].rank = (stu[i].score==stu[i-1].score) ? stu[i-1].rank : i+1;
        printf("%013lld %d %d %d\n", stu[i].id, stu[i].rank, stu[i].loc,  stu[i].loc_rank);
    }

}

//相同成绩，id小的在前
//数据大了会超时，用stl的sort试试，用第一种排名方法stl也还会超时，要用第二种
//输出学号的时候要13位格式输出，否则最后一个用例不超时但会错误
int main(int argc, char *argv[])
{
    fun1();//
}
