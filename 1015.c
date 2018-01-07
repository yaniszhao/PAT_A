#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//n<10^5,二进制的时候最长，2^17为128K所以20肯定够
#define MAX 20


#define DEBUG 0

int IsPrime(int n)
{
	int i;
	if (n==1) return 0;//有可能是1，否则有一个用例不过
	for (i=2; i<=sqrt(n); i++) {
		if (n%i==0) return 0;
	}
	return 1;
}

int GetReverNumWithRadix(int n, int radix)
{
	int m,cnt=0,i,sum=0;
	char str[MAX];
	do {
		//注意m和n的先后顺序，否则n被更新
		//m=n%radix;
		//str[cnt++]=m;
		str[cnt++]=n%radix;
		n=n/radix;
	}while(n!=0);

	//printf("rev:");
	for (i=0; i<cnt; i++) {
		//printf("%d", str[i]);
		//sum+=str[i]*pow(radix, cnt-i-1);
		sum = sum*radix+str[i];
	}
	//putchar('\n');
	return sum;
}

void fun1()
{
	int n,d;
	int tmp;
	while (1) {
		scanf("%d", &n);
		if (n<0) break;
		scanf("%d", &d);
		/*if (!IsPrime(n)) {
			printf("No\n");
			continue;
		}*/
		tmp=GetReverNumWithRadix(n, d);
		//printf("tmp:%d\n", tmp);
		//还要判断它自己是不是素数，否则一个用例不过
		if (IsPrime(tmp) && IsPrime(n))
			printf("Yes\n");
		else
			printf("No\n");
	}

}

int main(int argc, char *argv[])
{
	fun1();

}