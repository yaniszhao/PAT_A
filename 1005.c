#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 102

#define DEBUG 0


void ShowNumInEng(char c)
{
/*can use array 
cahr* arr[10] = {"zero", "one", "two", "three", "four", \
"five", "six", "seven", "eight", nine"};*/
	switch (c) {
		case '0': printf("zero");break;
		case '1': printf("one");break;
		case '2': printf("two");break;
		case '3': printf("three");break;
		case '4': printf("four");break;
		case '5': printf("five");break;
		case '6': printf("six");break;
		case '7': printf("seven");break;
		case '8': printf("eight");break;
		case '9': printf("nine");break;
	}
}

void fun1()
{
	char s[MAX]={0};
	int i,len,sum=0;
	scanf("%s", s);
	len = strlen(s);
	for (i=0; i<len; i++) {
		sum += s[i]-'0';
	}

	snprintf(s, MAX, "%d", sum);
	len = strlen(s);
	if (len>0) ShowNumInEng(s[0]); 
	for (i=1; i<len; i++) {
		putchar(' ');
		ShowNumInEng(s[i]);
	}

#if DEBUG
	printf("\nnum:%d\n", sum);
	printf("s:%s\n", s);
#endif
}

int main(int argc, char *argv[])
{
	fun1();


}