#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTIME 1e7//10000
#define MAXTIMESTR 10
#define MAX 10//10000
#define TABLEMAX 11//101

#define TimeToSec(h, m, s) (h*3600+m*60+s)


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


void HandWaitQueForVip(Player wait[], int index, int *tail)
{
    int i;
    for (i=index; i<*tail-1; i++)
        wait[i]=wait[i+1];
    *tail=*tail-1;
}

void SecToTime(char time[], int sec)
{
    int h,m,s;
    h=sec/3600;
    m=sec%3600/60;
    s=sec%60;
    sprintf(time, "%02d:%02d:%02d", h, m, s);
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
    int ftables, vtables, wpeople, vpeople;
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
        if (player[tail].ptime>120) player[tail].ptime=120;
        player[tail].ptime=player[tail].ptime*60;//改成秒
        if (player[tail].atime>=21*3600) continue;
        tail++;
    }
    
    scanf("%d%d", &m, &k);
    for (i=0; i<m; i++) {//init tables
        tables[i].endtime=8*3600;
        tables[i].vip=0;
        tables[i].cnt=0;
    }
    for (i=0; i<k ; i++) {
        scanf("%d", &j);
        tables[j-1].vip=1;//假设从0开始，题目上没说清
    }
    
    SortPlayer(player, tail);

    while (head!=tail) {
        endtime=GetEndTime(tables, m);
        ftables=0; vtables=0;
        for (i=0; i<m; i++) {//计算空余的桌子
            if (tables[i].endtime==endtime) {
                ftables++;
                if (tables[i].vip==1) vtables++;
            }
        }
        
        if (endtime>=21*3600)//要加等号
            break;
        
        while (player[head].atime<=endtime)//等待的人入列
            wait[wtail++]=player[head++];
        
        wpeople=wtail-whead;
        vpeople=GetVipPeopleNumFromWait(wait, whead, wtail);
        
        while (ftables>0 && wpeople>0) {//有空桌且有人
            if (vtables>0 && vpeople>0) {//有vip桌有vip人：最小vip桌配最早vip人
                tindex=GetVipTableIndex(tables, endtime, m);
                windex=GetVipPeopleIndexFromWait(wait, whead, wtail);
                wait[windex].start=endtime;//确定开始时间
                wait[windex].wtime=endtime-wait[windex].atime;//确定等待时间
                visited[vtail++]=wait[windex];//放入已访问队列
                tables[tindex].cnt++;
                tables[tindex].endtime=endtime+wait[windex].ptime;//更新时间
                HandWaitQueForVip(wait, windex, &wtail);//把vip从等待队列中去除
                ftables--; vtables--;
                wpeople--; vpeople--;
            }
            else if (vtables>0 && vpeople==0) {//有vip桌无vip人：有普通桌配普通人，无普通桌vip桌配普通人
                if (ftables-vtables>0) {//有普通桌
                    tindex=GetNormalTableIndex(tables, endtime, m);
                    windex=whead;
                    wait[windex].start=endtime;
                    wait[windex].wtime=endtime-wait[windex].atime;
                    visited[vtail++]=wait[windex];
                    tables[tindex].cnt++;
                    tables[tindex].endtime=endtime+wait[windex].ptime;
                    whead++;
                    ftables--;
                    wpeople--;
                }
                else {//无普通桌
                    tindex=GetVipTableIndex(tables, endtime, m);
                    windex=whead;
                    wait[windex].start=endtime;
                    wait[windex].wtime=endtime-wait[windex].atime;
                    visited[vtail++]=wait[windex];
                    tables[tindex].cnt++;
                    tables[tindex].endtime=endtime+wait[windex].ptime;//更新时间
                    whead++;
                    ftables--; vtables--;
                    wpeople--;
                }
            }
            else {//无vip桌：按顺序分配
                tindex=GetNormalTableIndex(tables, endtime, m);
                windex=whead;
                wait[windex].start=endtime;
                wait[windex].wtime=endtime-wait[windex].atime;
                visited[vtail++]=wait[windex];
                tables[tindex].cnt++;
                tables[tindex].endtime=endtime+wait[windex].ptime;
                whead++;
                ftables--;
                wpeople--; vpeople=(visited[tail-1].vip==1?vpeople-1:vpeople);
            }
        }

        nextendtime=GetNextEndTime(tables, m, endtime);
        while (ftables>0) {//还有空桌，要更新时间，要考虑后一个桌面最小时间和玩家最小时间哪个小
            tindex=GetTableIndex(tables, endtime, m);
            tables[tindex].endtime=player[head].atime<nextendtime?player[head].atime:nextendtime;
            ftables--;
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

/*
1、一桌一人：
    vip桌：直接入
    普通桌：直接入
2、一桌多人：
    vip桌：队列有vip入vip
    普通桌：入队列第一个
3、多桌一人：
    vip人：有vip桌，入最小的vip桌；没vip桌，入最小的普通桌
    普通人：有普通桌，入最小的普通桌；没普通桌，入最小的vip桌
4、多桌多人：
    while （桌大于0且人大于0）
        有vip桌有vip人：最小vip桌配最早vip人
        有vip桌无vip人：有普通桌配普通人，无普通桌vip桌配普通人
        无vip桌：按顺序分配
 有了第四个，可以不要前面三个
*/

int main(int argc, char *argv[])
{
    fun1();

}
