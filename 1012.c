#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2000

#define DEBUG 0

enum SUB{
	ENUM_C=1,
	ENUM_M,
	ENUM_E,
	ENUM_A
};

int sort(int A[], int n)
{//注意：当有前面两个成绩相同时，第三个人的排名为3不是2，所以sort函数不用去掉重复项
	int i, j, t, tmp, max=0;
	for (i=0; i<n-1; i++) {
		t = i;
		for (j=i+1; j<n; j++) {
			t = A[j]>A[t]?j:t;
		}
		tmp = A[i];
		A[i] = A[t];
		A[t] = tmp;
	}
/*	for (i=1,t=0; i<n; i++) {
		if (A[i]<A[t]) {
			A[++t] = A[i];
		}
	}*/
	return t+1;
}

int GetNo(int A[], int score)
{
	int i;
	for (i=0; i<MAX; i++){
		if (A[i]==score) return i+1;
	}
	return 0;
}

void GetNoAndSub(int arr[], int C[], int M[], int E[], int A[], int *no, int *sub)
{
	int cno, mno, eno, ano;
	int maxno, maxsub;
	cno = GetNo(C, arr[ENUM_C]);
	mno = GetNo(M, arr[ENUM_M]);
	eno = GetNo(E, arr[ENUM_E]);
	ano = GetNo(A, arr[ENUM_A]);
#if DEBUG
	printf("%d %d %d %d\n", cno, mno, eno, ano);
#endif
	maxno=ano;
	maxsub=ENUM_A;
	if (cno<maxno) {
		maxno=cno;
		maxsub=ENUM_C;
	}
	if (mno<maxno) {
		maxno=mno;
		maxsub=ENUM_M;
	}
	if (eno<maxno) {
		maxno=eno;
		maxsub=ENUM_E;
	}
	*no=maxno;
	*sub=maxsub;
}

int IsIdInArr(int arr[][5], int n, int id)
{
	int i;
	for (i=0; i<n; i++) {
		if (arr[i][0]==id)
			return i;
	}
	return -1;
}

void fun1()
{//注意:当有前面两个成绩相同时，第三个人的排名为3不是2，所以sort函数不用去掉重复项
	int arr[MAX][5];
	int C[MAX], M[MAX], E[MAX], A[MAX];
	int cmax=0, mmax=0, emax=0, amax=0;
	char MAP[5]={'x', 'C', 'M', 'E', 'A'};
	int n,m;
	int i,j,tmp,id;
	int no, sub;


	scanf("%d %d", &n, &m);
	getchar();
	for (i=0; i<n; i++) {
		scanf("%d %d %d %d", &arr[i][0], &arr[i][1], &arr[i][2], &arr[i][3]);
		getchar();
		arr[i][4] = (arr[i][1]+arr[i][2]+arr[i][3])/3;// 3.0 + 0.5;
		C[i] = arr[i][1];
		M[i] = arr[i][2];
		E[i] = arr[i][3];
		A[i] = arr[i][4];
	}

	cmax = sort(C, n);
	mmax = sort(M, n);
	emax = sort(E, n);
	amax = sort(A, n);
#if DEBUG
	for (i=0; i<cmax; i++) {
		printf("%d ", C[i]);
	}
	putchar('\n');
	for (i=0; i<mmax; i++) {
		printf("%d ", M[i]);
	}
	putchar('\n');
	for (i=0; i<emax; i++) {
		printf("%d ", E[i]);
	}
	putchar('\n');
	for (i=0; i<amax; i++) {
		printf("%d ", A[i]);
	}
	putchar('\n');
#endif

	for (i=0; i<m; i++) {
		scanf("%d", &id);
		getchar();
		if ((tmp=IsIdInArr(arr, n, id)) != -1) {//important
			GetNoAndSub(arr[tmp], C, M, E, A, &no, &sub);
			printf("%d %c\n", no, MAP[sub]);
		}
		else {
			printf("N/A\n");
		}
	}

}



int main(int argc, char *argv[])
{
	fun1();
}