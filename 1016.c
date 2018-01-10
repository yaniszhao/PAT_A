#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NAMEMAX 21
#define DAYHOUR 24
#define NUMMAX 1000

#define DEBUG 0

typedef struct stRecord {
	char name[NAMEMAX];
	char flag;//0-online,1-offline
	int mon;
	int day;
	int hour;
	int min;
} Record;

void Swap(Record *rec[], int x, int y)
{
	Record r;
	memcpy(&r, rec[x], sizeof(Record));
	memcpy(rec[x], rec[y], sizeof(Record));
	memcpy(rec[y], &r, sizeof(Record));
}

int IsALessB(Record *rec[], int x, int y)
{
	Record *a, *b;
	a=rec[x];
	b=rec[y];
	if (strcmp(a->name, b->name)<0) return 1;
	else if (strcmp(a->name, b->name)==0){
		if (a->mon<b->mon) return 1;
		else if (a->mon==b->mon) {
			if (a->day<b->day) return 1;
			else if (a->day==b->day) {
				if (a->hour<b->hour) return 1;
				else if (a->hour==b->hour) {
					if (a->min<b->min) return 1;
					else
						return 0;
				}
			}
		}
	}
	return 0;
}

void Sort(Record *rec[], int cnt)
{
	int i, j, min;
	for (i=0; i<cnt-1; i++) {
		min=i;
		for (j=i+1; j<cnt; j++) {
			if (IsALessB(rec, j, min))
				min=j;
		}
		Swap(rec, i, min);
	}
}

int GetMinutes(Record *r1, Record *r2)
{
	int d1, h1, m1, d2, h2, m2;
	d1=r1->day;
	h1=r1->hour;
	m1=r1->min;
	d2=r2->day;
	h2=r2->hour;
	m2=r2->min;
	return (d2-d1)*24*60+(h2-h1)*60+(m2-m1);
}

float GetToll(Record *r1, Record *r2, int price[], int *mins)
{
	int d1, h1, m1, d2, h2, m2;
	int tick, sum=0;
	d1=r1->day;
	h1=r1->hour;
	m1=r1->min;
	d2=r2->day;
	h2=r2->hour;
	m2=r2->min;
	for (tick=0; (d1!=d2)||(h1!=h2)||(m1!=m2); tick++) {
		sum+=price[h1];
		if (++m1==60) {
			m1=0;
			if (++h1==24) {
				h1=0;
				++d1;
			}
		}
	}
	//printf("%02d:%02d:%02d  %02d:%02d:%02d\n", d1, h1, m1, d2, h2, m2);
	*mins = tick;
	return sum/100.0;
}

void fun1()
{//之前用例不能过是最后打印的时候没有对sum判断
	int price[DAYHOUR];
	int n;
	int i,j,k;
	char cflag[10];
	char lastname[NAMEMAX]={'z'};
	int lastmon=0;
	Record *rec[NUMMAX], *p;
	int tmin,cnt=0;
	float tfee, sum;

	for (i=0; i<DAYHOUR; i++)
		scanf("%d", &price[i]);
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		p=(Record*)malloc(sizeof(Record));
		scanf("%s %d:%d:%d:%d %s", p->name, &p->mon, &p->day, &p->hour, &p->min, cflag);
		p->flag = !strcmp(cflag, "on-line") ? 0 : 1;
		rec[cnt++]=p;
	}
#if DEBUG
	for (i=0; i<cnt; i++) {
		p=rec[i];
		printf("%s %02d:%02d:%02d:%02d %d\n", p->name, p->mon, p->day, p->hour, p->min, p->flag);
	}
	putchar('\n');
	fflush(stdout);
#endif
	Sort(rec, cnt);
#if DEBUG
	for (i=0; i<cnt; i++) {
		p=rec[i];
		printf("%s %02d:%02d:%02d:%02d %d\n", p->name, p->mon, p->day, p->hour, p->min, p->flag);
	}
	putchar('\n');
	fflush(stdout);
#endif


	for (i=0; i<cnt; ) {
		p=rec[i];
		//if (strcmp(lastname, p->name)) {
		//注意memcpy要长度加一把\0也拷贝过去
		memcpy(lastname, p->name, strlen(p->name)+1);
		lastmon=0;
		sum=0;
		//注意k<cnt和strcmp的顺序，如果k<cnt在后面strcmp会越界
		for (k=i+1; k<cnt && !strcmp(lastname, rec[k]->name); k++) {
			if (rec[k-1]->flag!=0 || rec[k]->flag!=1) 
				continue;

			if (lastmon!=rec[k-1]->mon) {
				printf("%s %02d\n", rec[k-1]->name, rec[k-1]->mon);
				lastmon=rec[k-1]->mon;
			}

			tfee=GetToll(rec[k-1], rec[k], price, &tmin);			
			sum+=tfee;
			printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", \
					rec[k-1]->day,rec[k-1]->hour,rec[k-1]->min, \
					rec[k]->day,rec[k]->hour,rec[k]->min, \
					tmin, tfee);
		}
        if (sum!=0)
            printf("Total amount: $%.2f\n", sum);
		//fflush(stdout);
		i=k;
	}

}

//===============================================================

typedef struct stRecord2 {
    char name[NAMEMAX];
    char flag;//0-online,1-offline
    int mon;
    int day;
    int hour;
    int min;
    int tm;
} Record2;

void Swap2(Record2 rec[], int x, int y)
{
    Record2 r;
    memcpy(&r, &rec[x], sizeof(r));
    memcpy(&rec[x], &rec[y], sizeof(r));
    memcpy(&rec[y], &r, sizeof(r));
}

int IsALessB2(Record2 rec[], int x, int y)
{
    Record2 *a, *b;
    a=&rec[x];
    b=&rec[y];
    if (strcmp(a->name, b->name)<0) return 1;
    else if (strcmp(a->name, b->name)>0) return 0;
    else {
        if (a->mon!=b->mon)
            return a->mon<b->mon;
        else {
            if (a->tm<b->tm) return 1;
            else return 0;
        }
    }
}

void Sort2(Record2 rec[], int cnt)
{
    int i, j, min;
    for (i=0; i<cnt-1; i++) {
        min=i;
        for (j=i+1; j<cnt; j++) {
            if (IsALessB2(rec, j, min))
                min=j;
        }
        Swap2(rec, i, min);
    }
}

float GetToll2(Record2 *r1, Record2 *r2, int price[], int *mins)
{
    int d1, h1, m1, d2, h2, m2;
    int tick, sum=0;
    d1=r1->day;
    h1=r1->hour;
    m1=r1->min;
    d2=r2->day;
    h2=r2->hour;
    m2=r2->min;
    for (tick=0; (d1!=d2)||(h1!=h2)||(m1!=m2); tick++) {
        sum+=price[h1];
        if (++m1==60) {
            m1=0;
            if (++h1==24) {
                h1=0;
                ++d1;
            }
        }
    }
    *mins = tick;
    return sum/100.0;
}

void fun2()
{
    int price[DAYHOUR];
    int n;
    int i,j,k;
    char cflag[10];
    char lastname[NAMEMAX]={'z'};
    int lastmon=0;
    Record2 rec[NUMMAX], *p;
    int tmin,cnt=0;
    float tfee, sum;
    
    for (i=0; i<DAYHOUR; i++)
        scanf("%d", &price[i]);
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        p=&rec[i];
        scanf("%s %d:%d:%d:%d %s", p->name, &p->mon, &p->day, &p->hour, &p->min, cflag);
        p->flag = !strcmp(cflag, "on-line") ? 0 : 1;
        p->tm=p->day*24*60+p->hour*60+p->min;
    }
    cnt=i;
    Sort2(rec, cnt);
    
    for (i=0; i<cnt; ) {
        p=&rec[i];
        //注意memcpy要长度加一把\0也拷贝过去
        memcpy(lastname, p->name, strlen(p->name)+1);
        lastmon=0;
        sum=0;
        //注意k<cnt和strcmp的顺序，如果k<cnt在后面strcmp会越界
        for (k=i+1; k<cnt; k++) {
            if (strcmp(lastname, rec[k].name)) break;
            if (rec[k-1].flag!=0 || rec[k].flag!=1) continue;
            //if (rec[k-1].mon!=rec[k].mon) continue;
            
            if (lastmon!=rec[k-1].mon) {
                printf("%s %02d\n", rec[k-1].name, rec[k-1].mon);
                lastmon=rec[k-1].mon;
            }
            
            tfee=GetToll2(&rec[k-1], &rec[k], price, &tmin);
            sum+=tfee;
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", \
                   rec[k-1].day,rec[k-1].hour,rec[k-1].min, \
                   rec[k].day,rec[k].hour,rec[k].min, \
                   tmin, tfee);
        }
        if (sum!=0)//不加这个判断的话，中间两个用例过不了
            printf("Total amount: $%.2f\n", sum);
        i=k;
    }
}

int main(int argc, char *argv[])
{
    fun1();//加上sum的判断后就可以全过了，fun2是多余的
    //fun2();
}
