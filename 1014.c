#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PEOMAX 1001
#define WINMAX 20
#define LINEMAX 11
#define TIMEMAX 1e5

#define DEBUG 0

int IsMin(int linenum[], int idx, int n)
{
	int i;
	for (i=0; i<n; i++)
		if (linenum[i]<linenum[idx])
			return 0;
	return 1;
}

void IntToStr(int mins, char *str)
{
	int h, m;
	h=mins/60 + 8;
	m=mins%60;
	sprintf(str, "%02d:%02d", h, m);
	str[5]=0;
}

int IsLinequeEmpty(int linenum[], int n)
{
	int i;
	for (i=0; i<n; i++)
		if (linenum[i]>0)
			return 0;
	return 1;
}

int LinequeNum(int linenum[], int n)
{
	int i, cnt=0;
	for (i=0; i<n; i++)
		cnt+=linenum[i];
	return cnt;
}

void fun1()
{
	int lineque[WINMAX][LINEMAX];
	int linenum[WINMAX]={0};
	int head[WINMAX], tail[WINMAX];
	int wait[PEOMAX], whead, wtail;
	int sttime[PEOMAX],endtime[PEOMAX];
	int n,m,k,q;
	int mins[PEOMAX];
	int qIdx[PEOMAX];
	int i,j, cur, tick=0;
	char str[6];

	whead=1,wtail=1;
	for (i=0; i<WINMAX; i++) {
		head[i]=tail[i]=0;
	}

	for (i=0; i<PEOMAX; i++) {
		sttime[i]=endtime[i]=-1;
	}

	scanf("%d%d%d%d", &n,&m,&k,&q);
	for (i=1; i<=k; i++) {
		scanf("%d", &mins[i]);
		wait[wtail++]=i;
	}

	for (i=0; i<q; i++) {
		scanf("%d", &qIdx[i]);
	}

#if DEBUG
	printf("%d %d %d %d\n", n,m,k,q);
	for (i=0; i<q; i++)
		printf("%d ", qIdx[i]);
	putchar('\n');
	for (i=1; i<=k; i++) 
		printf("%d ", wait[i]);
	putchar('\n');
	fflush(stdout);
#endif

	//下面已经包含了第一次的赋值就不用这个
	/*//first inque
	for (j=0; j<n*m && j<k; j++) {
		for (i=0; i<n; i++) {//windows
			//if (whead==wtail) break;//have j<k,do not need this
			if (linenum[i]<m && IsMin(linenum, i, n)) {
				lineque[i][tail[i]]=wait[whead++];//inque
				tail[i]=(tail[i]+1)%LINEMAX;
				++linenum[i];
				break;
			}
		}		
	}

	//first set time
	for (i=0; i<n; i++) {//windows
		if (linenum[i]<1) continue;
		cur=lineque[i][head[i]];
		if (sttime[cur]==-1) 
			sttime[cur]=0;
	}*/

#if DEBUG
	for (i=0; i<n; i++) {//windows
		for (j=head[i]; j<tail[i]; j++) {
			printf("%d ", lineque[i][j]);
		}
		putchar('\n');
	}
	for (i=1; i<=k; i++) 
		printf("%d ", sttime[i]);
	putchar('\n');
#endif

	//tick
	//for (tick=0; tick<60*9 && !IsLinequeEmpty(linenum, n); tick++) {
	for (tick=0; tick<60*9; tick++) {
		//out peopeo
		for (i=0; i<n; i++) {//windows
			if (linenum[i]<1) continue;
			cur=lineque[i][head[i]];
			if (sttime[cur]+mins[cur]==tick) {
				endtime[cur]=tick;
				head[i]=(head[i]+1)%LINEMAX;//outque
				--linenum[i];
			}
		}
		
		//if (whead==wtail) continue;

		//in peopeo
		/*for (i=0; i<n; i++) {//windows
			if (whead==wtail) break;//empty
			if (linenum[i]<m && IsMin(linenum, i, n)) {
				lineque[i][tail[i]]=wait[whead++];//inque
				tail[i]=(tail[i]+1)%LINEMAX;
				++linenum[i];
			}
		}*/
		//有上面的第一次赋值就不用这个，用上面注释的
		while (LinequeNum(linenum, n)<n*m && whead!=wtail) {
			for (i=0; i<n; i++) {//windows
				if (linenum[i]<m && IsMin(linenum, i, n)) {
					lineque[i][tail[i]]=wait[whead++];//inque
					tail[i]=(tail[i]+1)%LINEMAX;
					++linenum[i];
					break;
				}
			}		
		}

		//set time
		for (i=0; i<n; i++) {//windows
			if (linenum[i]>=1) {
				cur=lineque[i][head[i]];
				if (sttime[cur]==-1) 
					sttime[cur]=tick;
			}
		}
#if DEBUG
	for (i=0; i<n; i++) {//windows
		for (j=head[i]; j<tail[i]; j++) {
			printf("%d ", lineque[i][j]);
		}
		putchar('\n');
	}
	for (i=1; i<=k; i++) 
		printf("%d ", sttime[i]);
	putchar('\n');
#endif
	}

	for (i=0; i<q; i++) {
		cur=qIdx[i];
		if (sttime[cur]!=-1) {
			IntToStr(sttime[cur]+mins[cur], str);
			printf("%s\n", str);
		}
		else
			printf("Sorry\n");
	}

}
//===============================================

typedef struct stWindow {
    int lineque[LINEMAX];
    int linenum;
    int head;
    int tail;
} Window;

typedef struct stWaitQue {
    int lineque[PEOMAX];
    int linenum;
    int head;
    int tail;
} WaitQue;

int IsMin2(Window w[], int idx, int n)
{
    int i;
    for (i=0; i<n; i++)
        if (w[i].linenum<w[idx].linenum)
            return 0;
    return 1;
}

int CountWindowQueNum(Window w[], int n)
{
    int i, cnt=0;
    for (i=0; i<n; i++)
        cnt+=w[i].linenum;
    return cnt;
}

void fun2() {
    Window window[WINMAX];
    WaitQue wait;
    int sttime[PEOMAX], endtime[PEOMAX];
    int n, m, k, q;
    int mins[PEOMAX];
    int qIdx[PEOMAX];
    int i, j, cur, mintime;
    char str[6];

    wait.head=0, wait.tail=0, wait.linenum=0;
    for (i=0; i<WINMAX; i++) {
        window[i].head=window[i].tail=0;
        window[i].linenum=0;
    }

    for (i=0; i<PEOMAX; i++) {
        sttime[i]=endtime[i]=-1;
    }

    scanf("%d%d%d%d", &n,&m,&k,&q);
    for (i=1; i<=k; i++) {
        scanf("%d", &mins[i]);
        wait.lineque[wait.tail++]=i;
        wait.linenum++;
    }

    for (i=0; i<q; i++) {
        scanf("%d", &qIdx[i]);
    }

    //first inque
   /*for (j=0; j<n*m && j<k; j++) {
       for (i=0; i<n; i++) {//windows
           if (window[i].linenum<m && IsMin2(window, i, n)) {
               window[i].lineque[window[i].tail]=wait.lineque[wait.head++];//inque
               window[i].tail=(window[i].tail+1)%LINEMAX;
               window[i].linenum++;
               break;
           }
       }
   }*/
    for (j=0,i=0; j<n*m && j<k; j++, i=(i+1)%n) {
        window[i].lineque[window[i].tail]=wait.lineque[wait.head];//inque
        window[i].tail=(window[i].tail+1)%LINEMAX;
        window[i].linenum++;
        wait.head++;
        wait.linenum--;
    }

    //first set time
    for (i=0; i<n; i++) {//windows
        if (window[i].linenum<1) continue;
        cur=window[i].lineque[window[i].head];
        if (sttime[cur]==-1)
            sttime[cur]=0;
    }

    while (CountWindowQueNum(window, n) > 0) {
        mintime=TIMEMAX;
        for (i=0; i<n; i++) {//get mimtime
            if (window[i].linenum<1) continue;
            cur=window[i].lineque[window[i].head];
            mintime=(mins[cur]+sttime[cur] < mintime)?(mins[cur]+sttime[cur]):mintime;
        }

        for (i=0; i<n; i++) {//outque
            if (window[i].linenum<1) continue;
            cur=window[i].lineque[window[i].head];
            if (mins[cur]+sttime[cur] == mintime) {
                window[i].head=(window[i].head+1)%LINEMAX;
                window[i].linenum--;
            }
        }

        //if (wait.linenum==0 || mintime>=9*60) continue;//不能放在这影响set time

        for (i=0; i<n; i++) {//windows,inque
            if (wait.linenum==0) break;//no people wait, or time full
            if (window[i].linenum<m && IsMin2(window, i, n)) {
                window[i].lineque[window[i].tail]=wait.lineque[wait.head];//inque
                window[i].tail=(window[i].tail+1)%LINEMAX;
                window[i].linenum++;
                wait.head++;
                wait.linenum--;
            }
        }

        //set time
        for (i=0; i<n; i++) {//windows
            if (window[i].linenum<1) continue;
            cur=window[i].lineque[window[i].head];
            if (sttime[cur] == -1)
                sttime[cur]=mintime;
        }
    }

    for (i=0; i<q; i++) {
        cur=qIdx[i];
        if (sttime[cur]!=-1 && sttime[cur]<9*60) {
            IntToStr(sttime[cur]+mins[cur], str);
            printf("%s\n", str);
        }
        else
            printf("Sorry\n");
    }

}

int main(int argc, char *argv[])
{
   //fun1();
   fun2();
}