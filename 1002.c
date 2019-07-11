#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define F_ZERO 0.000001
typedef struct st_poly
{
	int exp;
	float coe;
} poly;

void fun1()
{
	poly A[MAX]={0}, B[MAX]={0}, C[MAX]={0};
	int na, nb;
	int i,j,k;

	// if (scanf("%d ", &na) == EOF) 
	// 	return 1;
	scanf("%d ", &nb); //肯定有数据的，上面个判断没必要了
	for (i=0; i<na; i++) {
		scanf("%d %f", &A[i].exp, &A[i].coe);
		getchar();
	}

	scanf("%d ", &nb);	
	for (i=0; i<nb; i++) {
		scanf("%d %f", &B[i].exp, &B[i].coe);
		getchar();
	}

	for (i=0,j=0,k=0; i<na&&j<nb&&k<MAX; ) {
		if (A[i].exp > B[j].exp) {
			C[k].exp = A[i].exp;
			C[k].coe = A[i].coe;
			i++;
			k++;
		}
		else if (A[i].exp < B[j].exp) {
			C[k].exp = B[j].exp;
			C[k].coe = B[j].coe;
			j++;
			k++;
		}
		else {
			C[k].exp = A[i].exp;
			C[k].coe = A[i].coe + B[j].coe;
			i++;
			j++;
			//系数可能两个正负相同抵消了，则此项就不要了
			if (abs(C[k].coe) > F_ZERO)	k++;
		}
	}

	//有一个扫描完了，但是另外一个还有剩余。
	for (; i<na; k++,i++) {
		C[k].exp = A[i].exp;
		C[k].coe = A[i].coe;
	}

	for (; j<nb; k++,j++) {
		C[k].exp = B[j].exp;
		C[k].coe = B[j].coe;
	}

	printf("%d", k);
	for (i=0; i<k; i++) printf(" %d %.1f", C[i].exp, C[i].coe);
}

void fun2()
{
	//用一个数组表示所有的指数项，里面装系数，最后逆向打印
	//参考cpp的代码
}

//输出多项式A和B的和
int main(int argc, char *argv[])
{
	fun1();
}