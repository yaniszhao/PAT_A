#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDMAX 16
#define TIMEMAX 20

#define DEBUG 0

typedef struct stUser {
	 char id[IDMAX];
	 char sttime[TIMEMAX];
	 char endtime[TIMEMAX];
} User;

int tm2int(char *tm)
{
	/*int hour = (tm[0]-'0')*10 + tm[1]-'0';
	int min = (tm[3]-'0')*10 + tm[4]-'0';
	int sec = (tm[6]-'0')*10 + tm[7]-'0';*/
	int hour,min,sec;
	sscanf(tm, "%d:%d:%d", &hour, &min, &sec);
	return hour*3600+min*60+sec;
}

void fun1()
{
	int m;
	int i, mintime=0, maxtime=0;
	User* user;
	
	scanf("%d", &m);
	getchar();
	user = (User*)malloc(m * sizeof(User));
	for (i=0; i<m; i++) {
		//scanf("%d:%d:%d %d:%d:%d", &h1, &m1, &s1, &h2, &m2, &s2);
		scanf("%s %s %s", user[i].id, user[i].sttime, user[i].endtime);
		getchar();
		if (tm2int(user[i].sttime)<tm2int(user[mintime].sttime))
			mintime = i;
		if (tm2int(user[i].endtime)>tm2int(user[maxtime].endtime))
			maxtime = i;
	}

	printf("%s %s", user[mintime].id, user[maxtime].id);

}

int main(int argc, char *argv[])
{
	fun1();


}