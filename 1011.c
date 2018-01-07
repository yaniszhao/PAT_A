#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 3

#define DEBUG 0


void fun1()
{
	float arr[MAX];
	char TAB[MAX]={'W','T','L'};
	int i,j, tmax;
	float sum=1.0;

	for (i=0; i<MAX; i++) {
		scanf("%f %f %f", &arr[0], &arr[1], &arr[2]);
		getchar();
		for (j=1,tmax=0; j<MAX; j++) {
			tmax = arr[j]>arr[tmax]?j:tmax;
		}
		sum *= arr[tmax];
		printf("%c ", TAB[tmax]);
	}

	printf("%.2f", (sum * 0.65 - 1) * 2);
}



int main(int argc, char *argv[])
{
	fun1();
}