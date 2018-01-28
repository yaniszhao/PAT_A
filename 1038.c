#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000
#define MAXSTR 9


int cmp(const void *a, const void *b)
{
    char s1[2*MAXSTR];
    char s2[2*MAXSTR];
    memcpy(s1, a, MAXSTR); strcat(s1, b);
    memcpy(s2, b, MAXSTR); strcat(s2, a);
    return strcmp(s1, s2)>0;
}

void fun1()
{
    char str[MAX][MAXSTR];
    char *numstr;
    int n;
    int i, allzero=1;
    
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf(" %s", str[i]);
    
    qsort(str, n, MAXSTR, cmp);
    
    numstr=malloc(n*MAXSTR);
    numstr[0]='\0';
    for (i=0; i<n; i++) {
        //一组字符串不超不8位，int肯定够了，不用考虑是否用更大的空间来存转换后的值
        if (atoi(str[i])!=0) allzero=0;//判断是否全0
        //if (i==0 && str[i][0]=='0')//第一是0要消除
        //  strcat(numstr, &str[i][1]);
        if (i==0)//前面可能不止一个0，所以还是用这个方法
            sprintf(numstr, "%d", atoi(str[i]));
        else
            strcat(numstr, str[i]);
    }
    
    if (allzero) printf("0");
    else printf("%s", numstr);
}

//贪心算法，每次只找最小值的字符串，即使开头一样或有重叠，下一字符串的开头也还是它自己
int main(int argc, char *argv[])
{
    fun1();
}

