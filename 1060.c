#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 102
#define MAXSTR (MAX)//和MAX相同都能过，不用乘以2

void Strip(int n, char s[])
{
    int i, len;
    len=strlen(s);
    for (i=n; i<len-1 && s[i]!='\0'; i++) {
        if (s[i]=='.') {s[i]='\0'; return;}
        else s[i]='0';
    }
}

void PrintScience(int n, char s[])
{
    int i;
    printf("0.");
    for (i=0; i<n; i++)
        printf("%c", s[i]);
    printf("*10^%d", (int)strlen(s));
}

void fun1()
{
    int n;
    char s1[MAX+1], s2[MAX+1];
    scanf("%d %s %s", &n, s1, s2);
    Strip(n, s1);
    Strip(n, s2);
    if (strcmp(s1, s2)==0) {
        printf("YES ");
        PrintScience(n, s1);
    }
    else {
        printf("NO ");
        PrintScience(n, s1);
        putchar(' ');
        PrintScience(n, s2);
    }
}
//===================================
int Strip2(char arr[], char **s)
{
    int i, len, fpos=-1;
    int tenbits;//十的个数
    len=strlen(arr);
    for (i=0; i<len; i++) //先找到小数点
        if (arr[i]=='.') {fpos=i; break;}
    if (fpos>-1) {//有小数点,处理小数点
        for (i=fpos; i<len-1; i++)
            arr[i]=arr[i+1];
        len--;
        arr[len]='\0';
        tenbits=fpos;
    }
    else tenbits=len;

    //处理前面的无效0
    for (i=0; i<len && arr[i]=='0'; i++, tenbits--);
    *s=&arr[i];
    //后面补零
    for (i=strlen(*s); i<MAX; i++)
        (*s)[i]='0';

    (*s)[MAX]='\0';
    //如果处理后第一个都还‘0’，那么就是0或者0.000...要返回0
    return (*s)[0]=='0'?0:tenbits;
}

void PrintScience2(char s[], int n, int len)
{
    int i;
    printf("0.");
    for (i=0; i<n; i++)
        printf("%c", s[i]);
    printf("*10^%d", len);
}

void fun2()
{
    int n;
    char arr1[MAXSTR], arr2[MAXSTR];//用于存储实际数据
    char *s1, *s2;//除0外第一个非0地址
    int len1, len2;//10的个数
    int i, flag=1;
    scanf("%d %s %s", &n, arr1, arr2);
    len1=Strip2(arr1, &s1);
    len2=Strip2(arr2, &s2);
    if (len1!=len2) flag=0;
    else {
        for (i=0; i<n; i++)
            if (s1[i]!=s2[i]) {flag=0; break;}
    }

    if (flag==1) {
        printf("YES ");
        PrintScience2(s1, n, len1);
    }
    else {
        printf("NO ");
        PrintScience2(s1, n, len1);
        putchar(' ');
        PrintScience2(s2, n, len2);
    }
}

//要考虑0包括0和0.0
//要考虑前面有可能有多个0的情况
//要考虑小数点第一位不能为0，除非整个数就是0，比如输入为0.001
int main(int argc, char *argv[])
{
   fun2();
}

