#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXSTU 40000
#define MAXSCH 100
#define MAXCHO 5

typedef struct {
    int id;
    int Ge;
    int Gi;
    int final;
    int choice[MAXCHO];
    int rank;
} Stu;

bool cmp(Stu a, Stu b)
{
    if (a.final==b.final) {
        if (a.Ge==b.Ge)
            return a.id<b.id;
        else return a.Ge>b.Ge;
    }
    else return a.final>b.final;
    //return a.final!=b.final?a.final>b.final:a.Ge > b.Ge;
}

bool cmp2(int a, int b)
{
    return a<b;
}

void fun1()
{
    int quota[MAXSCH];
    vector<int> school[MAXSCH];
    int lastrank[MAXSCH];//不用这个变量不好得到最后一个排名
    vector<Stu> stu;
    int n,m,k;
    int i,j,choice;
    Stu tmpstu;
    //记录输入
    scanf("%d%d%d", &n, &m, &k);
    for (i=0; i<m; i++)
        scanf("%d", &quota[i]);
    for (i=0; i<n; i++) {
        scanf("%d%d", &tmpstu.Ge, &tmpstu.Gi);
        tmpstu.final=tmpstu.Ge+tmpstu.Gi;//除以2可能精度丢失
        tmpstu.id=i;//记录id排序后可能会乱
        for (j=0; j<k; j++)
            scanf("%d", &tmpstu.choice[j]);
        stu.push_back(tmpstu);
    }
    //排序获得排名
    sort(stu.begin(), stu.end(), cmp);
    stu[0].rank=1;
    for (i=1; i<stu.size(); i++)
        if (stu[i].final==stu[i-1].final&&stu[i].Ge==stu[i-1].Ge)
            stu[i].rank=stu[i-1].rank;
        else stu[i].rank=i+1;
    //确定学校
    for (i=0; i<stu.size(); i++) {
        for (j=0; j<k; j++) {
            choice=stu[i].choice[j];
            if (school[choice].size()<quota[choice]) {
                lastrank[choice]=stu[i].rank;
                school[choice].push_back(stu[i].id);
                break;
            }//和选择的学校最后一名的排名一样,不要用stu[school[choice][school[choice].size()-1]].rank
            else if (stu[i].rank==lastrank[choice]) {
                school[choice].push_back(stu[i].id);
                break;
            }
        }
    }
    //打印
    for (i=0; i<m; i++) {
        if (school[i].size()==0) {putchar('\n'); continue;}
        sort(school[i].begin(), school[i].end(), cmp2);
        printf("%d", school[i][0]);
        for (j=1; j<school[i].size(); j++)
            printf(" %d", school[i][j]);
        putchar('\n');
    }
}

//1、如果要考虑学生的志愿优先级的话，这题根本排不了序；所以按成绩的高低，
//成绩高的优先选择学校，即使学校的优先级没有后面的高，还是先录取它
//2、这题还有大小不确定的情况，因为学校可能超额，用c语言固定大小数组简直作死，还是用cpp吧
//3、获得学校最后排名的时候要用空间存储，光用最后一个学生的id两个用例错误，因为拍完序已经不是按id存的了
//4、加上lastrank关于学校的数组有点多了，可以考虑用结构体存了
int main(int argc, char *argv[])
{
   fun1();
}

