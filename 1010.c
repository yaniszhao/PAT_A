#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 11
#define MAXINT 0x7FFFFFFFFFFFFFFF
typedef long long LLONG;
int GetNumFromChar(char c)
{
    switch (c) {
        case '0'...'9': return c-'0';break;
        case 'a'...'z': return 10+c-'a';break;
        default: return 0;break;
    }
}

LLONG StrToIntWithRadix(char s[], LLONG radix)
{
    LLONG sum=0;
    int i;
    for (i=0; s[i]!='\0'; i++) {
        sum=sum*radix+GetNumFromChar(s[i]);
    }
    return sum;
}

LLONG HaveRadixToEqual(LLONG n1, char s[])
{
    LLONG i, j, maxn=1;
    for (i=0; s[i]!='\0'; i++) {
        //有j就不用再调一次函数
        maxn = (j=GetNumFromChar(s[i]))>maxn ? j : maxn;
    }
    
    for (i=maxn+1;i<MAXINT; i++) {
        //j用于调试看值
        if (n1==(j=StrToIntWithRadix(s, i))) return i;
    }
    
    return 0;
}

LLONG HaveRadixToEqual2(LLONG n1, char s[])
{
    LLONG i, j;
    LLONG l, r, mid;
    LLONG min=MAXINT, maxn=1;
    
    //if (!strcmp(s, "0")) return n1==0?1:0;
    
    for (i=0; s[i]!='\0'; i++) {
        //有j就不用再调一次函数
        maxn = (j=GetNumFromChar(s[i]))>maxn ? j : maxn;
    }
    
    l=maxn+1;
    j=StrToIntWithRadix(s, l);
    if (n1<j) return 0;
    if (n1==j) return l;
    r=n1+1;//10 a 1 10
    while (l<=r) {
        mid=(l+r)/2;//用直接加法可能会溢出
        //mid=l+(r-l)/2;
        j=StrToIntWithRadix(s, mid);
//        if (n1==j) {
//            min=mid<min?mid:min;
//            r=mid-1;
//        }
        if (j<0) r=mid-1;//考虑溢出的情况，否则有好几个用例过不了
        else if (n1==j) return mid;
        else if (n1<j) r=mid-1;
        else l=mid+1;
    }
    
    //return min==MAXINT?0:min;
    return 0;
}

LLONG HaveRadixToEqual3(LLONG n1, char s[])
{
    LLONG i, j;
    LLONG l, r, mid;
    LLONG min=MAXINT, maxn=1;
    
    for (i=0; s[i]!='\0'; i++) {
        //有j就不用再调一次函数
        maxn = (j=GetNumFromChar(s[i]))>maxn ? j : maxn;
    }
    
    l=maxn+1;
    r=MAXINT;
    while (l<=r) {
        //mid=(l+r)/2;//用直接加法可能会溢出
        mid=l+(r-l)/2;
        j=StrToIntWithRadix(s, mid);
        if (j<0) r=mid-1;//考虑溢出的情况，否则有好几个用例过不了
        else if (n1==j) {
            min=mid<min?mid:min;
            r=mid-1;
        }
        else if (n1<j) r=mid-1;
        else l=mid+1;
    }
    
    return min==MAXINT?0:min;
}

void fun1()
{
    char sn1[MAXLEN]={0}, sn2[MAXLEN]={0};
    int tag;
    LLONG n1, radix;
    char *p;
    LLONG flag;

    scanf("%s %s %d %lld", sn1, sn2, &tag, &radix);
    if (tag==1) {
        n1=StrToIntWithRadix(sn1, radix);
        p=sn2;
    }
    else {
        n1=StrToIntWithRadix(sn2, radix);
        p=sn1;
    }

    flag=HaveRadixToEqual2(n1, p);
    if (!flag) printf("Impossible");
    else printf("%lld", flag);
}

//1、要考虑radix的大小可能会超过int
//2、考虑最小的进制，比如出现的符号最大是1最小进制是2，出现的最大符号是a最小进制为11
//3、考虑转换成十进制时溢出之后变成负数
int main(int argc, char *argv[])
{
	fun1();

}
