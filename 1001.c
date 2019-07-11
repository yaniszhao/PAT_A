#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
void fun1()
{
	int a = 0, b = 0;
	char c[MAX] = {0};
	int len = 0;
	int start = 0;
	int first = 0;
	int i = 0;
	scanf("%d %d", &a, &b);
	//itoa(c, a+b, MAX);
	//sprintf(c, "%d", a+b);
	snprintf(c, MAX, "%d", a+b);
	//printf("c:%s\n", c);
	len = strlen(c);
	if (c[0] == '-') {
		len--;
		start = 1;
		printf("%c", c[0]);
	}
	first = len % 3;
	if (first) {
		for (; i < first; i++)
			printf("%c", c[i+start]);
		if (first != len)//-100 9
			putchar(',');
	}
	//for (i = 0; i < len - first; i++) {
	for (i = 1; i <= len - first; i++) {
		putchar(c[start+first+i-1]);
		//if (i>0 && i%3==0) putchar(',');
		if (i>0 && i%3==0 && i!=(len-first)) putchar(',');
	}
	putchar('\n');
}

void reverse(char a[], int l, int h)
{
	int i;
	char t;
	for(i=l; i<=(l+h)/2; i++) {//care i<=(l+h)/2,not i<(l+h)/2
		t=a[i];
		a[i] = a[h-i+l];
		a[h-i+l] = t;
	}
}
void fun2()
{
	int a, b;
	char c[MAX] = {0};
	char d[2*MAX] = {0};
	int len;
	int i,j;
	scanf("%d %d", &a, &b);
	snprintf(c, MAX, "%d", a+b);
	len = strlen(c);
	if (c[0] == '-') {
		len--;
		putchar(c[0]);
	}
	reverse(c, 0, strlen(c)-1);
	for(i=0, j=1; i<2*MAX && j<=len; i++, j++) {
		d[i]=c[j-1];
		if (j%3==0 && j!= len) d[++i]=',';
	}
	d[i]='\0';
	//reverse(d, 0, i-1);
	while(i>0)
		putchar(d[--i]);
}

void fun3()
{
	int a,b;
	char c[MAX]={0}; 
	int i,len;
	scanf("%d %d", &a, &b);
	snprintf(c, MAX, "%d", a+b);
	len = strlen(c);
	for (i=0;i<len;i++) {
		putchar(c[i]);
		if (c[i]=='-') continue;
		if ((len-i-1)%3==0 && i!=(len-1)) putchar(',');
	}
}

//格式化输出a+b的值，即对值加上逗号。如 -1000000+9=-999,991
//一开始考虑的是先反转再加逗号，然后反转回来；后来看到别人的代码，其实可以直接正着打印。
int main(int argc, char *argv[])
{
	//fun1();
	//fun2();
	fun3();
}
	