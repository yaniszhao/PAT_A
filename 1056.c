#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2000//原本大小为1000为了不让队列做循环，我扩大一倍肯定够

void fun1()
{
    int wei[MAX];
    int rank[MAX];
    int que_win[MAX], whead, wtail;
    int que_los[MAX], lhead, ltail;
    int np, ng;
    int i,j,k;
    int max,last,tmprank;

    whead=wtail=0;
    lhead=ltail=0;

    scanf("%d%d", &np, &ng);
    for (i=0; i<np; i++)
        scanf("%d", &wei[i]);
    for (i=0; i<np; i++) {
        scanf("%d", &j);
        que_win[wtail++]=j;
    }

    while (wtail-whead!=1) {//最后剩一个才退出
        last=wtail;
        while (whead!=last) {
            k=last-whead>=ng?ng:last-whead;
            for (j=whead+1,max=whead; j<whead+k; j++)
                if (wei[que_win[j]]>wei[que_win[max]])
                    max=j;//找到一组中最大的
            for (j=0; j<k; j++)
                if (whead==max) que_win[wtail++]=que_win[whead++];
                else que_los[ltail++]=que_win[whead++];
        }
        //处理失败人的排名
        tmprank=wtail-whead+1;//失败人的排名
        for (; lhead<ltail; lhead++)
            rank[que_los[lhead]]=tmprank;
    }
    rank[que_win[whead]]=1;//处理第一名

    if (np>0) printf("%d", rank[0]);
    for (i=1; i<np; i++) printf(" %d", rank[i]);
}

void fun2()
{
    int wei[MAX];
    int rank[MAX];
    int que_win[MAX], whead, wtail;
    int np, ng;
    int i,j,k;
    int max,last,tmprank;

    whead=wtail=0;
    scanf("%d%d", &np, &ng);
    for (i=0; i<np; i++)
        scanf("%d", &wei[i]);
    for (i=0; i<np; i++) {
        scanf("%d", &j);
        que_win[wtail++]=j;
    }

    while (wtail-whead>1) {//最后剩一个才退出
        last=wtail;
        tmprank=(wtail-whead+ng-1)/ng+1;//失败人的排名
        while (whead!=last) {
            k=last-whead>=ng?ng:last-whead;
            for (j=whead+1,max=whead; j<whead+k; j++)
                if (wei[que_win[j]]>wei[que_win[max]])
                    max=j;//找到一组中最大的
            for (j=0; j<k; j++)
                if (whead==max) que_win[wtail++]=que_win[whead++];
                else rank[que_win[whead++]]=tmprank;//处理失败人的排名
        }
    }
    rank[que_win[whead]]=1;//处理第一名

    if (np>0) printf("%d", rank[0]);
    for (i=1; i<np; i++) printf(" %d", rank[i]);
}

//当一组的人数不足ng的时候还是在里面选出最肥的那个
//每次判断失败的人的排名很好确定，优胜者的个数+1即为失败者的排名
//要想让队列不做循环把大小扩大一倍
//fun2优化了下失败的人的处理，节省了que_los数组，和循环赋值的代码
int main(int argc, char *argv[])
{
   fun2();
}

