#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

#define DEBUG 0


void fun1()
{
	int list[MAX]={0};
	int n;
	int i, cur=0, sum=0;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		scanf(" %d", &list[i]);
	}

	for (i=0; i<n; i++) {
		if (cur<list[i]) {//up
			sum += (list[i]-cur)*6;
		}
		else if (cur>list[i]) {//down
			sum += (cur-list[i])*4;
		}
		cur = list[i];
		sum += 5;
	}
	printf("%d", sum);
}

void fun2()
{
	int n;
	int i, tmp, cur=0, sum=0;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		scanf(" %d", &tmp);
		sum += cur<tmp?(tmp-cur)*6:(cur-tmp)*4;
		cur = tmp;
		sum += 5;
	}
	printf("%d", sum);
}

int main(int argc, char *argv[])
{
	//fun1();
	fun1();
}