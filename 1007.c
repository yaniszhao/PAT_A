#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
#define NEGMAX -1e5
#define DEBUG 0


void fun1()
{
	int n;
	int seq[MAX];
	int i,j,sum;
	int ls=0,ld=0,lsum;//line
	int s=0,d=0,maxsum=NEGMAX;
	int haspos=0;//has postive numver

	scanf("%d", &n);
	getchar();
	for (i=0; i<n; i++) {
		scanf("%d", &seq[i]);
		getchar();
		if (seq[i]>=0) haspos=1;//careful >= not >
	}

	if (!haspos) {
		//printf("0 0 %d", n-1);
		printf("0 %d %d", seq[0], seq[n-1]);
		return;
	}

	//core part
	for (i=0; i<n; i++) {
		sum = 0;
		lsum = NEGMAX;
		ls = i;
		for (j=i; j<n; j++) {
			sum += seq[j];
			if (sum>lsum) {
				lsum = sum;
				ld = j;
			}
		}
		if (lsum>maxsum) {
			maxsum = lsum;
			s = ls;
			d = ld;
		}
	}
	//printf("%d %d %d", maxsum, s, d);
	printf("%d %d %d", maxsum, seq[s], seq[d]);
}

int main(int argc, char *argv[])
{
	fun1();

}