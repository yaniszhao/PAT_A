#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXUSER 10001
#define MAXPROB 6


typedef struct {
    int id;
    int score[MAXPROB];//成绩下标1开始
    int total;//总分
    int perfect;//满分个数
    int subflag;//提交标识，按位对应
    int flag;//有效数据标识，按位对应
    int rank;
} User;

int cmp(const void *a, const void *b)
{
    User *x=(User *)a;
    User *y=(User *)b;
    if (y->total==x->total) {//先按总成绩
        if (y->perfect==x->perfect) return -1;//再按满分题目个数
        else  return y->perfect-x->perfect;//最后按id，本来就是从小到大的，故直接返回值
    }
    else return y->total-x->total;
}

void fun1()
{
    User user[MAXUSER];
    int probfull[MAXPROB];
    int n,k,m;
    int id, prob, score;
    int i,j,cnt=0;
    scanf("%d%d%d", &n, &k, &m);
    for (i=1; i<=k; i++)
        scanf("%d", &probfull[i]);
    memset(user, 0, MAXUSER*sizeof(user[0]));//全部初始为0
    for (i=0; i<m; i++) {
        scanf("%d%d%d", &id, &prob, &score);
        //无效数值处理
        if (score==-1) {
            //user[id].id=id;//想让它参与排序得有数据是有效的，有效的数值会赋值
            user[id].subflag=(user[id].subflag | 1<<prob);//某题参与
            continue;
        }
        else if (score<user[id].score[prob]) continue;//比它大肯定赋过值了
        //有效数据赋值
        user[id].total+=score-user[id].score[prob];
        if (score==probfull[prob]&&user[id].score[prob]!=score)
            user[id].perfect++;//满分题目个数
        user[id].id=id;
        user[id].score[prob]=score;
        user[id].subflag=(user[id].subflag | 1<<prob);//某题参与
        user[id].flag=(user[id].flag | 1<<prob);//某题有分
    }
    for (i=1; i<MAXUSER; i++) {
        //只要是有效数据全是0分也要参与排序，不能用total判别
        //if (user[i].flag==0||user[i].total==0)
        if (user[i].flag==0)//必须至少有一个有效数据才参与排序
            continue;
        user[cnt++]=user[i];
    }

    qsort(user, cnt, sizeof(user[0]), cmp);
    for (i=0; i<cnt; i++) {//也可以用个lastrank，直接在打印循环里获得rank，省去结构体的rank空间
        if (i==0) user[i].rank=1;
        else user[i].rank=user[i].total==user[i-1].total?user[i-1].rank:i+1;
    }
    for (i=0; i<cnt; i++) {
        printf("%d %05d %d", user[i].rank, user[i].id, user[i].total);
        for (j=1; j<=k; j++)
            if (user[i].subflag&1<<j) printf(" %d", user[i].score[j]);
            else printf(" -");
        putchar('\n');
    }
}

//1、全部编译失败或者没提交的人不参与排序，不是全部编译失败还是要参与排序
//2、编译失败但是属于提交了，所以不能输出'-'
//3、排序的条件：
//第一条件：总分最多的
//第二条件：得满分的个数
//第三条件：id序号
//4、只用一个flag只能知道是否有有效数据，是否让其排序；
//比如1有效2无效，让其参与排序，但不知道2是提交了没效还是根本没提交过；
//加入subflag是在有有效数据的情况下知道哪些是没有提交的
int main(int argc, char *argv[])
{
   fun1();
}

