#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define INF 1.0e7

typedef struct stSta {
    double price;
    double dis;
} Sta;

int n;
double cap, dst, avg;

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
        if (sta[i].dis-sta[u].dis <= cap*avg) continue;
        else  return i-u-1;
    }
    return i-u-1;
}

int HaveCheaperSta(Sta sta[], int u, int sub)
{
    int i,min=u;
    for (i=u+1; i<=u+sub; i++)
        if (sta[i].price<=sta[min].price) min=i;
    return min;
}

void fun1()
{
    Sta sta[MAX];
    int i,j;
    int sub_sta_cnt;
    double totalfee=0, curdis=0;
    double surplus=0;

    scanf("%lf%lf%lf%d", &cap, &dst, &avg, &n);
    for (i=0; i<n; i++) {
        scanf("%lf%lf", &sta[i].price, &sta[i].dis);
        sta[i].price=sta[i].price/avg;//换算成每走一米的价格
    }

    SortSta(sta);

    if (sta[0].dis==0){
        for (i=0; i<n;) {
            sub_sta_cnt=CountSubSta(sta, i);
            if (sub_sta_cnt==0) {//无法到达后面一站点, 不能直接用sta[n-1]表示，可能有两个隔太远了
                if (curdis+cap*avg < dst) {//无法到达终点
                    curdis=curdis+cap*avg;
                    surplus=0;
                    break;
                }
                else {//能到达终点
                    totalfee+=(dst-sta[i].dis-surplus)*sta[i].price;
                    curdis=dst;
                    surplus=0;
                    break;
                }
            }
            else {//能到达后面至少一个站点
                j=HaveCheaperSta(sta, i, sub_sta_cnt);
                if (i==j) {//没有更便宜的，或者相同的, 加满到最后一个站点或终点
                    if (curdis+cap*avg >= dst) {//能开到终点
                        totalfee+=(dst-sta[i].dis-surplus)*sta[i].price;
                        curdis=dst;
                        surplus=0;
                        break;
                    }
                    else {//不能到达终点则加满到到站点
                        totalfee+=(cap*avg-surplus)*sta[i].price;
                        curdis=sta[i+sub_sta_cnt].dis;
                        surplus=cap*avg-(sta[i+sub_sta_cnt].dis-sta[i].dis);
                        i=i+sub_sta_cnt;
                    }
                }
                else {//有更便宜的
                    totalfee+=(sta[j].dis-sta[i].dis-surplus)*sta[i].price;
                    curdis=sta[j].dis;
                    surplus=0;
                    i=j;//到下一个站点
                }
            }
        }
    }

    if (curdis!=dst)
        printf("The maximum travel distance = %.2lf", curdis);
    else
        printf("%.2lf", totalfee);

}


/*
 每个站点判断一次：
 当前站点最远开到哪
 在最远范围内：
 1、能找到比当前站点更便宜的站点，加恰好到那个站的油
 2、不能找到最便宜的，但能找到一个最远的站点，加满油开到那个站点
 3、没有站点，但终点在范围内，加恰好到终点的油
 4、前面三个都不满足，加满油后开到的就是最远的距离
 */
int main(int argc, char *argv[])
{
    fun1();
}



