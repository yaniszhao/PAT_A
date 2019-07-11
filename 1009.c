#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001
#define F_ZERO 0.0000001

void fun1()
{
	float A[MAX]={0};
	float B[MAX]={0};
	float C[2*MAX-1]={0};
	int n;
	int i, j, exp;
	float coe;

	/*for (i=0; i<MAX; i++) {
		A[i] = F_ZERO;
		B[i] = F_ZERO;		
	}
	for (i=0; i<2*MAX-1; i++) {
		C[i] = F_ZERO;
	}*/

	scanf("%d", &n);
	for (i=0; i<n; i++){
		scanf(" %d %f", &exp, &coe);
		A[exp] = coe;
	}
	getchar();
	scanf("%d", &n);
	for (i=0; i<n; i++){
		scanf(" %d %f", &exp, &coe);
		B[exp] = coe;
	}
	getchar();
	for (i=0; i<MAX; i++) {
		for (j=0; j<MAX; j++) {
			if (A[i]!=0 && B[j]!=0) {
				C[i+j] += A[i] * B[j];
			}
		}
	}

	for (n=0,i=2*MAX-2; i>=0; i--)
		if (C[i]!=0) n++;//use '!=', maybe negative number
	printf("%d", n);
	for (i=2*MAX-2; i>=0; i--)
		if (C[i]!=0) printf(" %d %.1f", i, C[i]);

}

//A和B可以动态分配内存来存数据，以节省空间，但是C最好是固定分配空好点；
//不然找其对于的指数的位置还要遍历和分配空间。
int main(int argc, char *argv[])
{
	fun1();
}