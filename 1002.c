/*
1002. A+B for Polynomials (25)

时间限制
400 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
This time, you are supposed to find A+B where A and B are two polynomials.

Input

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. It is given that 1 <= K <= 10，0 <= NK < ... < N2 < N1 <=1000.

Output

For each test case you should output the sum of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 2 1.5 1 2.9 0 3.2
*/

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

int fun1()
{
	poly A[MAX]={0}, B[MAX]={0}, C[MAX]={0};
	int na, nb;
	int i,j,k;

	if (scanf("%d ", &na) == EOF) 
		return 1;//no new case
	for (i=0; i<na; i++) {
		scanf("%d %f", &A[i].exp, &A[i].coe);
		getchar();
	}
	//printf("%d\n", na);
	//for (i=0; i<na; i++) printf("%d %.1f\n", A[i].exp, A[i].coe);
	
	scanf("%d ", &nb);
	
	for (i=0; i<nb; i++) {
		scanf("%d %f", &B[i].exp, &B[i].coe);
		getchar();
	}
	//printf("%d\n", nb);
	//for (i=0; i<nb; i++) printf("%d %.1f\n", B[i].exp, B[i].coe);

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
			if (abs(C[k].coe) > F_ZERO)
				k++;//careful, if coe is 0, ignore it
		}
	}
	for (; i<na; k++,i++) {
		C[k].exp = A[i].exp;
		C[k].coe = A[i].coe;
	}
	for (; j<nb; k++,j++) {
		C[k].exp = B[j].exp;
		C[k].coe = B[j].coe;
	}

	//printf("%d\n", k);
	//for (i=0; i<k; i++) printf("%d %.1f\n", C[i].exp, C[i].coe);
	printf("%d", k);
	for (i=0; i<k; i++) printf(" %d %.1f", C[i].exp, C[i].coe);

	return 0;
}

void fun2()
{
	//用一个数组表示所有的指数项，里面装系数，最后逆向打印

}

int main(int argc, char *argv[])
{
	/*while (!fun1()) 
		putchar('\n');*/
	//donnot need while
	fun1();

}