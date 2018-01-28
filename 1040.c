#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001

int IsSymmetric(char s[], int l, int r)
{
    int i, j;
    if (l==r) return 1;
    //不要用r-i，因为i不是从0开始的，如果要从0开始，函数要从l的那个字符串开始传进来
    //(r-l-1)/2别忘了+l
    for (i=l,j=0; i<=(r-l-1)/2+l; i++, j++) {
        if (s[i]!=s[r-j]) return 0;
    }
    return 1;
}

int IsSymmetric2(char s[], int len)
{//还是这种方便一点
    int i;
    if (len==1) return 1;
    //不要用r-i，因为i不是从0开始的，如果要从0开始，函数要从l的那个字符串开始传进来
    for (i=0; i<=(len-1)/2; i++) {
        if (s[i]!=s[len-1-i]) return 0;
    }
    return 1;
}

void fun1()
{//最先开始的不一定是最大的，比如abbabb最大应该是5不是4
    char s[MAX];
    int i,j;
    int len, max=1;
    //scanf("%s", s);//遇到空格就停了
    fgets(s, MAX, stdin);//用gets不安全
    len=(int)strlen(s);
    //去掉换行符
    if (s[len-1]=='\n') {s[len-1]='\0'; len--;}
    if (len==0) {printf("0"); return;}
    for (i=0; i<len-1; i++) {
        for (j=len-1; j>i; j--) {
            if (s[i]==s[j]){
                if (IsSymmetric(s, i, j)) {
                //if (IsSymmetric2(&s[i], j-i+1)) {
                    max=j-i+1;
                    break;
                }
            }
        }
        if (max!=1) break;
    }
    printf("%d", max);
}

void fun2()
{
    char s[MAX];
    int i,j;
    int len, max=1,tmpmax=1;

    fgets(s, MAX, stdin);//用gets不安全
    len=(int)strlen(s);
    //去掉换行符
    if (s[len-1]=='\n') {s[len-1]='\0'; len--;}
    if (len==0) {printf("0"); return;}
    
    for (i=0; i<len-1; i++) {
        for (j=len-1; j>i; j--) {
            if (s[i]==s[j]){
                if (IsSymmetric(s, i, j)) {
                //if (IsSymmetric2(&s[i], j-i+1)) {
                    tmpmax=j-i+1;
                    break;
                }
            }
        }
        max=tmpmax>max?tmpmax:max;
    }
    printf("%d", max);
}


//最先开始的不一定是最大的，比如abbabb最大应该是5不是4
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}


