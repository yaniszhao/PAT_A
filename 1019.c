#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//10e9取二进制时，符号占最多空间也小于2e32即3G左右(2e10为1024)
#define MAXLEN 32

typedef struct stString {
    int arr[MAXLEN];
    int len;
} Str;

void Int2StrWithBase(int n, int b, Str *s)
{
    s->len=0;
    if (n==0)//要对0做判断，否则有一个用例不过
        s->arr[s->len++]=0;
    
    while (n!=0) {
        s->arr[s->len++]=n%b;
        n=n/b;
    }
}

int IsPalindromicNum(Str *s)
{
    int i;
    for (i=0; i<=(s->len-1)/2; i++) {
        if (s->arr[i] != s->arr[s->len-1-i])
            return 0;
    }
    return 1;
}

void fun1()
{
    Str s;
    int n,b;
    int i, flag;
    
    scanf("%d%d", &n, &b);
    Int2StrWithBase(n, b, &s);
    flag=IsPalindromicNum(&s);
    printf("%s\n", flag?"Yes":"No");
    if (s.len>=1) printf("%d", s.arr[s.len-1]);
    for (i=s.len-2; i>=0; i--)
        printf(" %d", s.arr[i]);
    
}

int main(int argc, char *argv[])
{
    fun1();
}
