#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXTIME 1e7
#define MAXTIMESTR 10
#define TimeToSec(h, m, s) (h*3600+m*60+s)
#define MIN(a, b) (a<b?a:b)

typedef struct stPlayer {
    int atime;//arrive
    int ptime;//play time
    int vip;
    int start;//start time
    int wtime;//wait time
} Player;

typedef struct stTable {
    int endtime;
    int vip;
    int cnt;
} Table;

vector<Player> player,waitq,visited;
vector<Table> tables;

bool cmp1(Player a, Player b)
{
    return a.atime<b.atime;
}

bool cmp2(Player a, Player b)
{
    if (a.start==b.start)
        return a.atime<b.atime;
    else return a.start<b.start;
}

int GetEndTime()
{
    int endtime=MAXTIME;
    for (auto it : tables)
        if (it.endtime<endtime) endtime=it.endtime;
    return endtime;
}

int GetNextEndTime(int endtime)
{
    int next=MAXTIME;
    for (auto it : tables)
        if (it.endtime!=endtime && it.endtime<next) next=it.endtime;
    return next;
}

void SecToTime(char time[], int sec)
{
    int h,m;
    h=sec/3600; sec%=3600;
    m=sec/60; sec%=60;
    sprintf(time, "%02d:%02d:%02d", h, m, sec);
}

void fun1()
{
    Player tmp;
    int ftables, fvtables, vpeople=0;
    char s1[MAXTIMESTR], s2[MAXTIMESTR];
    int n,m,k;
    int hour,min,sec;
    int i,j;
    int tindex,windex;//table index and wait index
    int endtime, nextendtime;

    scanf("%d", &n);
    for (i=0; i<n ; i++) {
        scanf("%d:%d:%d %d %d", &hour, &min, &sec, &tmp.ptime, &tmp.vip);
        tmp.atime=TimeToSec(hour, min, sec);
        if (tmp.atime>=21*3600) continue;
        if (tmp.ptime>120) tmp.ptime=120;
        tmp.ptime=tmp.ptime*60;//改成秒
        player.push_back(tmp);
    }

    scanf("%d%d", &m, &k);
    tables.resize(m);
    for (auto &it : tables) {//要改值要加引用
        it.endtime=8*3600;
        it.vip=0;
        it.cnt=0;
    }
    for (i=0; i<k; i++) {
        scanf("%d", &j);
        tables[j-1].vip=1;//下标从0开始
    }

    sort(player.begin(), player.end(), cmp1);

    while (!player.empty() || !waitq.empty()) {
        //桌子空出时间
        endtime=GetEndTime();
        if (endtime>=21*3600) break;//超出时间，退出
        //空桌数
        ftables=0; fvtables=0;//free tables, free vip tables
        for (auto it : tables) {//计算空余的桌子
            if (it.endtime==endtime) {
                ftables++;
                if (it.vip==1) fvtables++;
            }
        }
        //等待的人入列
        while (!player.empty() && player[0].atime<=endtime) {
            waitq.push_back(player[0]);
            if ((waitq.end()-1)->vip) vpeople++;
            player.erase(player.begin());
        }

        //有空桌且有人，分配桌子
        while (ftables>0 && !waitq.empty()) {
            if (fvtables>0 && vpeople>0) {//有vip桌有vip人：最小vip桌配最早vip人
                for (tindex=0; tindex<tables.size(); tindex++)
                    if (tables[tindex].vip && tables[tindex].endtime==endtime) break;
                for (windex=0; windex<waitq.size(); windex++)
                    if (waitq[windex].vip) break;
            }
            else {//无vip桌或有vip桌没vip人：按顺序分配
                for (tindex=0; tindex<tables.size(); tindex++)
                    if (tables[tindex].endtime==endtime) break;
                windex=0;
            }
            waitq[windex].start=endtime;//确定开始时间
            waitq[windex].wtime=endtime-waitq[windex].atime;//确定等待时间
            visited.push_back(waitq[windex]);//放入已访问队列
            tables[tindex].cnt++;
            tables[tindex].endtime=endtime+waitq[windex].ptime;//更新时间
            waitq.erase(waitq.begin()+windex);
            if (tables[tindex].vip) fvtables--;
            if ((visited.end()-1)->vip) vpeople--;
            ftables--;
        }

        //还有空桌但没人了，要更新空桌时间
        if (ftables>0 && !player.empty()) {//waitq肯定是空
            nextendtime=GetNextEndTime(endtime);
            nextendtime=MIN(nextendtime, player[0].atime);
            for (auto &it : tables)
                if (it.endtime==endtime) it.endtime=nextendtime;
        }
    }

    //sort(visited.begin(), visited.end(), cmp2);
    for (auto it : visited) {
        SecToTime(s1, it.atime);
        SecToTime(s2, it.start);
        printf("%s %s %d\n", s1, s2, (it.wtime+30)/60);//四舍五入
    }
    for (i=0; i<tables.size(); i++)
        if (i==0) printf("%d", tables[i].cnt);
        else printf(" %d", tables[i].cnt);
}

//1、把握好table和wait、player的关系，继续循环的条件是(endtime小于9点 且 (wait不空或player不空))；
//搞清楚这3个关系，循环内判断endtime或者wait、player都可以，之前用player判断会遗漏wait还有的情况
//2、分配桌子的情况其实很简单：有vip桌和vip人则优先分配vip，其他情况按顺序分配就行了
//我之前想复杂了，认为没vip人的时候普通人优先分配普通桌，其实是按顺序分配
//3、循环分配完后如果还有空桌，要根据最近的结束时间和下一位玩家时间更新结束时间
//4、等待时间要四舍五入
int main(int argc, char *argv[])
{
    fun1();
}
