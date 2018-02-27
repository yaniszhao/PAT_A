#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

typedef struct stSta {
    float price;
    int dis;
} Sta;

int cap, dst, avg, n;

void SortSta(Sta sta[])
{
    Sta t;
    int i,j,min;
    for (i=0; i<n-1; i++) {
        min=i;
        for (j=i+1; j<n; j++)
            if (sta[j].dis<sta[min].dis) min=j;
        t=sta[i];
        sta[i]=sta[min];
        sta[min]=t;
    }
}

int CountSubSta(Sta sta[], int u)
{//计算当前站点可直达得站点个数，在终点前
    int i;
    for (i=u+1; i<n; i++) {
        if (sta[i].dis-sta[u].dis <= cap) continue;
        else  return i-u-1;
    }
    return i-u-1;
}

int HaveCheaperSta(Sta sta[], int u, int sub)
{
    int i,min=u;
    for (i=u+1; i<=u+sub; i++)
        if (sta[i].price<sta[min].price)
            return i;//找到第一个就要退出
    return min;
}

void fun1()
{
    Sta sta[MAX];
    int i,j, min;
    int sub_sta_cnt,curdis=0,surplus=0;
    float totalfee=0;

    scanf("%d%d%d%d", &cap, &dst, &avg, &n);
    cap=cap*avg;//换成米
    for (i=0; i<n; i++) {
        scanf("%f%d", &sta[i].price, &sta[i].dis);
        sta[i].price=sta[i].price/avg;//换算成每走一米的价格
    }

    SortSta(sta);

    if (sta[0].dis==0){
        for (i=0; i<n;) {
            sub_sta_cnt=CountSubSta(sta, i);
            if (sub_sta_cnt==0) {//无法到达后面一站点, 可能隔太远了或者是最后一个站点
                if (curdis+cap < dst) {//无法到达终点
                    totalfee+=sta[i].price*(cap-surplus);
                    curdis=curdis+cap;
                    break;
                }
                else {//能到达终点
                    totalfee+=sta[i].price*(dst-sta[i].dis-surplus);
                    curdis=dst;
                    break;
                }
            }
            else {//能到达后面至少一个站点
                j=HaveCheaperSta(sta, i, sub_sta_cnt);
                if (i==j) {//后面没有更便宜的，加满到后面最便宜的站点或终点
                    if (curdis+cap >= dst) {//能开到终点
                        totalfee+=sta[i].price*(dst-sta[i].dis-surplus);
                        curdis=dst;
                        break;
                    }
                    else {//不能到达终点则加满到到后面最小站点
                        min=i+1;
                        for (j=i+2; j<=i+sub_sta_cnt; j++)
                            if (sta[j].price<sta[min].price) min=j;//找到后面最小的站点
                        totalfee+=sta[i].price*(cap-surplus);
                        curdis=sta[min].dis;
                        surplus=cap+sta[i].dis-sta[min].dis;
                        i=min;
                    }
                }
                else {//有更便宜的
                    if (sta[j].dis<dst) {//在终点前，去站点
                        totalfee+=sta[i].price*(sta[j].dis-sta[i].dis-surplus);
                        curdis=sta[j].dis;
                        surplus=0;
                        i=j;
                    }
                    else {//在终点后，去终点，如果在输入做处理可以不要这个
                        totalfee+=sta[i].price*(dst-sta[i].dis-surplus);
                        curdis=dst;
                        break;
                    }
                }
            }
        }
    }

    if (curdis!=dst)
        printf("The maximum travel distance = %.2f", (float)curdis);
    else
        printf("%.2f", totalfee);

}

/*
 每个站点判断一次：
 1、能找到比当前站点更便宜的站点：
     1）在终点前，加恰好到那个站的油
     2）在终点后，去终点
 2、不能找到更便宜的：
     1）当前是最便宜的，能到终点去终点
     2）不能去终点去后面最便宜的站点：
 3、后面没有站点或者站点太远，加满开到最远
 */
//1、不能找到最便宜的要去后面最便宜的，不是去最后一个站点
//2、找到一个更便宜的就要返回，不是找能达到的最便宜的，因为中间的油价可能比当前的贵
//3、cpp的代码有点小区别可以对比看下
int main(int argc, char *argv[])
{
    fun1();
}



