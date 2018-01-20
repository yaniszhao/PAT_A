#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
typedef long long LLONG;

int IsPal(LLONG n)
{
    char s[MAX];
    int i, len;
    sprintf(s, "%lld", n);
    len=(int)strlen(s);
    for (i=0; i<=(len-1)/2; i++)
        if (s[i]!=s[len-i-1]) return 0;
    return 1;
}

LLONG reverse(LLONG n)
{
    char s[MAX];
    int i, len;
    char t;
    len=(int)strlen(s);
    for (i=0; i<=(len-1)/2; i++) {
        t=s[i];
        s[i]=s[len-i-1];
        s[len-i-1]=t;
    }
    return atoll(s);
}

void fun1()
{
    LLONG n;//用int不行，因为有十位
    int k;
    int i,cnt=0;
    
    scanf("%lld%d", &n, &k);
    if (IsPal(n)==0) {
        for (i=0; i<k; i++) {
            n=n+reverse(n);
            cnt++;
            if (IsPal(n)) break;
        }
    }
    
    printf("%lld\n%d", n, cnt);
    
}

//===================================================

int IsPal2(char s[])
{
    int len=(int)strlen(s);
    int i;
    for (i=0; i<=(len-1)/2; i++)
        if (s[i]!=s[len-i-1]) return 0;
    return 1;
}

void AddReverse(char s[])
{
    char s2[MAX];
    int len=(int)strlen(s);
    int i;
    int tmp,over=0;
    
    for (i=len-1; i>=0; i--) {//将相加后的值逆序存到s2
        tmp=s[i]-'0'+s[len-i-1]-'0'+over;
        if (tmp>=10) {
            over=1;
            s2[len-i-1]=tmp-10+'0';
        }
        else {
            over=0;
            s2[len-i-1]=tmp+'0';
        }
    }
    
    if (over) {//处理溢出
        s2[len]='1';
        s2[len+1]='\0';
    }
    else {
        s2[len]='\0';
    }
    
    //把逆序变为正序并赋给s
    len=(int)strlen(s2);
    for (i=len-1; i>=0; i--)
        s[len-i-1]=s2[i];
    s[len]='\0';
}

void fun2()
{
    char s[MAX];
    int k;
    int i, cnt=0;
    
    scanf("%s %d", s, &k);
    
    if (IsPal2(s)==0) {
        for (i=0; i<k; i++) {
            AddReverse(s);
            cnt++;
            if (IsPal2(s)) break;
        }
    }
    printf("%s\n%d", s, cnt);
}

//LONG LONG也可能不够，因为最多可以加100次，还是要换成字符
//MAX开到30还有两个不过，开到40有一个不过，开到50全过
//看来加法加100次数值还是很大
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}
