#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 9//tret为四位，但为13的整数倍的时候不会有tret，所以9就够了，不用10

char *map1[]={"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
char *map2[]={NULL, "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};

void EarthToMars(char s[])
{
    int num=atoi(s);
    if (num<13) printf("%s\n", map1[num]);
    else {
        //13的整数倍不打印tret,但是就为0的时候要打印tret，所以还是有用
        if (num%13==0) printf("%s\n", map2[num/13]);
        else printf("%s %s\n", map2[num/13], map1[num%13]);
    }
}

void MarsToEarth(char s[])
{
    int a,b;
    if (s[3]==' ') {
        s[3]=0;
        for (a=1; strcmp(map2[a], s); a++);
        for (b=0; strcmp(map1[b], &s[4]); b++);
        printf("%d\n", a*13+b);
    }
    else {//tret走这里
        for (a=0; a<13&&strcmp(map1[a], s); a++);//小心死循环
        if (a==13) {//为13的整数倍的时候第一个找不到
            for (a=1; strcmp(map2[a], s); a++);
            printf("%d\n", a*13);
        }
        else printf("%d\n", a);
    }
}

void fun1()
{
    char s[MAX];
    int n;
    int i,len;;
    scanf("%d\n", &n);
    for (i=0; i<n; i++) {
        fgets(s, 9, stdin);
        len=strlen(s);
        s[len-1]=0;
        if (s[0]>='0'&&s[0]<='9') EarthToMars(s);
        else MarsToEarth(s);
    }
}

//1、只有值为0的时候才会用到tret，13的整数倍不用tret
//2、小心死循环
int main(int argc, char *argv[])
{
   fun1();
}

