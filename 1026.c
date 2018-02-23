#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTIME 1e7
#define MAXTIMESTR 10
#define MAX 10000
#define TABLEMAX 100

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

int cmp(const void *a, const void *b)
{
    Player *x=(Player *)a;
    Player *y=(Player *)b;
    return x->atime-y->atime;
}

void SortPlayer(Player arr[], int n)
{
    int i,j,min;
    Player t;
    for (i=0; i<n-1; i++) {
        min=i;
        for (j=i+1; j<n; j++) {
            if (arr[j].atime < arr[min].atime)
                min=j;
        }
        memcpy(&t, &arr[i], sizeof(arr[0]));
        memcpy(&arr[i], &arr[min], sizeof(arr[0]));
        memcpy(&arr[min], &t, sizeof(arr[0]));
    }
}

int GetEndTime(Table t[], int n)
{
    int i, endtime=MAXTIME;

    for (i=0; i<n; i++)
        if (t[i].endtime<endtime) endtime=t[i].endtime;
    return endtime;
}

int GetNextEndTime(Table t[], int n, int endtime)
{
    int i, next=MAXTIME;

    for (i=0; i<n; i++) {
        if (t[i].endtime==endtime) continue;
        if (t[i].endtime<next) next=t[i].endtime;
    }
    return next;
}

int GetVipPeopleNumFromWait(Player wait[], int head, int tail)
{
    int i, num=0;
    for (i=head; i<tail; i++)
        if (wait[i].vip==1) num++;
    return num;
}

int GetVipTableIndex(Table t[], int endtime, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (t[i].endtime==endtime && t[i].vip==1)
            return i;//返回下标
    return -1;
}

int GetNormalTableIndex(Table t[], int endtime, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (t[i].endtime==endtime && t[i].vip==0)
            return i;//返回下标
    return -1;
}

int GetTableIndex(Table t[], int endtime, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (t[i].endtime==endtime)
            return i;//返回下标
    return -1;
}

int GetVipPeopleIndexFromWait(Player wait[], int head, int tail)
{
    int i;
    for (i=head; i<tail; i++)
        if (wait[i].vip==1) return i;
    return -1;
}

void HandWaitQue(Player wait[], int index, int *tail)
{
    int i;
    for (i=index; i<*tail-1; i++)
        wait[i]=wait[i+1];
    *tail=*tail-1;
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
    Player player[MAX];
    Player wait[MAX];
    Player visited[MAX];
    int head=0, tail=0;
    int whead=0, wtail=0;//wait que
    int vhead=0, vtail=0;//visited que
    Table tables[TABLEMAX];
    int ftables, fvtables, wpeople=0, vpeople=0;
    int n,m,k;
    int hour,min,sec;
    int i,j;
    int endtime, nextendtime;
    int tindex,windex;//table index and wait index
    char s1[MAXTIMESTR], s2[MAXTIMESTR];

    scanf("%d", &n);
    for (i=0; i<n ; i++) {
        scanf("%d:%d:%d %d %d", &hour, &min, &sec, &player[tail].ptime, &player[tail].vip);
        player[tail].atime=TimeToSec(hour, min, sec);
        if (player[tail].atime>=21*3600) continue;
        if (player[tail].ptime>120) player[tail].ptime=120;
        player[tail].ptime=player[tail].ptime*60;//改成秒
        tail++;
    }

    scanf("%d%d", &m, &k);
    for (i=0; i<m; i++) {//init tables
        tables[i].endtime=8*3600;
        tables[i].vip=0;
        tables[i].cnt=0;
    }
    for (i=0; i<k; i++) {
        scanf("%d", &j);
        tables[j-1].vip=1;//假设从0开始
    }

    //SortPlayer(player, tail);
    qsort(player, tail, sizeof(player[0]), cmp);

    while (head!=tail || whead!=wtail) {
        endtime=GetEndTime(tables, m);
        if (endtime>=21*3600) break;//要加等号

        ftables=0; fvtables=0;//free tables and vip tables
        for (i=0; i<m; i++) {//计算空余的桌子
            if (tables[i].endtime==endtime) {
                ftables++;
                if (tables[i].vip==1) fvtables++;
            }
        }

        while (head!=tail && player[head].atime<=endtime) {//等待的人入列
            wait[wtail++]=player[head++];
            wpeople++;
            if (wait[wtail-1].vip) vpeople++;
        }

        while (ftables>0 && wpeople>0) {//有空桌且有人
            if (fvtables>0 && vpeople>0) {//有vip桌有vip人：最小vip桌配最早vip人
                tindex=GetVipTableIndex(tables, endtime, m);
                windex=GetVipPeopleIndexFromWait(wait, whead, wtail);
            }
            else {//无vip桌：按顺序分配
                tindex=GetTableIndex(tables, endtime, m);
                windex=whead;
            }
            wait[windex].start=endtime;//确定开始时间
            wait[windex].wtime=endtime-wait[windex].atime;//确定等待时间
            visited[vtail++]=wait[windex];//放入已访问队列
            tables[tindex].cnt++;
            tables[tindex].endtime=endtime+wait[windex].ptime;//更新时间
            HandWaitQue(wait, windex, &wtail);//从等待队列中去除
            if (tables[tindex].vip) fvtables--;
            if (visited[vtail-1].vip) vpeople--;
            ftables--; wpeople--;
        }

        if (ftables>0 && head!=tail) {//还有空桌，要更新时间，要考虑后一个桌面最小时间和玩家最小时间哪个小
            nextendtime=GetNextEndTime(tables, m, endtime);
            nextendtime=MIN(nextendtime, player[head].atime);
            for (i=0; i<m; i++)
                if (tables[i].endtime==endtime) tables[i].endtime=nextendtime;
        }
    }

    for (i=vhead; i<vtail; i++) {
        SecToTime(s1, visited[i].atime);
        SecToTime(s2, visited[i].start);
        printf("%s %s %d\n", s1, s2, (visited[i].wtime+30)/60);
    }
    for (i=0; i<m; i++) {
        if (i==0) printf("%d", tables[i].cnt);
        else printf(" %d", tables[i].cnt);
    }
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

