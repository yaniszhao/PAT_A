#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 81
#define INF 1e4


void fun1()
{
    char s[MAX];
    int len;
    int n1,n2;//左右两边是n1,中间是n2(不包含n1的点的个数)
    int i,j;
    scanf("%s", s);
    len=(int)strlen(s);
    n1=(len+2)/3;//确定n1，因为是3边所以是除3加2
    if (2*n1+n1==len) n2=n1;//为什么这么我也不清楚，就是感觉这样可以
    else if (2*n1+n1-1==len) n2=n1-1;
    else n2=n1-2;
    for (i=0; i<n1; i++) {
        if (i!=n1-1) {//不是最后一行
            printf("%c", s[i]);
            for (j=0; j<n2; j++) putchar(' ');
            printf("%c", s[len-1-i]);
        }
        else {
            printf("%c", s[i]);
            for (j=0; j<n2; j++) putchar(s[i+j+1]);
            printf("%c", s[len-1-i]);
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    fun1();
}
