#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PEOMAX 10000
#define WINMAX 100
#define LINEMAX 1

#define DEBUG 0

typedef struct  stPerson {
	int hour;
	int min;
	int sec;
	int ptm;//processing time
} Person;


void Swap(Person per[], int x, int y)
{
	Person p;
	memcpy(&p, &per[x], sizeof(Person));
	memcpy(&per[x], &per[y], sizeof(Person));
	memcpy(&per[y], &p, sizeof(Person));
}

void Sort(Person per[], int cnt)
{
	int i, j, min;
	for (i=0; i<cnt-1; i++) {
		min=i;
		for (j=i+1; j<cnt; j++) {
			if ((per[j].hour*3600+per[j].min*60+per[j].sec) < \
				(per[min].hour*3600+per[min].min*60+per[min].sec))
				min=j;
		}
		Swap(per, i, min);
	}
}



void fun1()
{
	int lineque[WINMAX];
	int linenum[WINMAX]={0};
	Person wait[PEOMAX];
	int whead=0, wtail=0, cnt=0;
	int sttime[PEOMAX];
	int vset[PEOMAX]={0}, vcnt=0;
	int n,k;
	int i,j, cur, tick=0;
	int h,m,s,p;
	float sum=0;
	int tmp;

	for (i=0; i<PEOMAX; i++) {
		sttime[i]=-1;
	}

	scanf("%d%d", &n,&k);
	for (i=0; i<n; i++) {
		scanf("%d:%d:%d %d", &h,&m,&s,&p);
		if (h>=17&&(m>0||s>0)) continue;
		wait[cnt].hour=h;
		wait[cnt].min=m;
		wait[cnt].sec=s;
		wait[cnt].ptm=p;//>60?60:p;
		cnt++;
	}
	Sort(wait, cnt);
#if DEBUG
	printf("%d %d\n", n,k);
	for (i=0; i<cnt; i++) {
		printf("%d %d %d %d", wait[i].hour, wait[i].min, wait[i].sec, wait[i].ptm);
		putchar('\n');
	}
	putchar('\n');
	fflush(stdout);
#endif

	//tick
	//不改成秒有一个用例过不了
	for (tick=0; tick<3600*9; tick++) {
		//out peopeo
		for (i=0; i<k; i++) {//windows
			if (linenum[i]!=1) continue;
			cur=lineque[i];
			if (sttime[cur]+wait[cur].ptm*60==tick) {
				--linenum[i];//outque
			}
		}

		//in peopeo
		if (vcnt>=cnt) break;
		for (i=0; i<k; i++) {//windows
			if (linenum[i]==0) {
				for (j=0; j<cnt; j++) {
					if (!vset[j] && ((wait[j].hour-8)*3600+(wait[j].min)*60+wait[j].sec)<=tick) {
						lineque[i]=j;//inque
						vset[j]=1;
						vcnt++;
						++linenum[i];
						break;
					}					
				}				
			}
		}

		//set time
		for (i=0; i<k; i++) {//windows
			if (linenum[i]==1) {
				cur=lineque[i];
				if (sttime[cur]==-1) 
					sttime[cur]=tick;
			}
		}

#if DEBUG
	for (i=0; i<k; i++)//windows
		printf("%d ", lineque[i]);
	putchar('\n');
	for (i=0; i<cnt; i++) 
		printf("%d ", sttime[i]);
	putchar('\n');
	fflush(stdout);
#endif
	}

	for (i=0; i<vcnt; i++) {
		tmp=((wait[i].hour-8)*3600+(wait[i].min)*60+wait[i].sec);
		//printf("%d ", tmp);
		sum+=sttime[i]/60.0-tmp/60.0;
	}
	//putchar('\n');
	if (vcnt==0)//好像没什么用
		printf("0.0\n");
	else {
		sum=sum/vcnt;
		printf("%.1f\n", sum);
	}

}

int main(int argc, char *argv[])
{
	fun1();

}