#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100
#define MAXSTR 258//0~256是257个，加个结束符就是258

void fun1()
{
    char s[MAX][MAXSTR];
    int len[MAX];
    int n;
    int i,j,min,cnt=0;
    int flag;
    scanf("%d", &n);
    getchar();//吸收第一行的换行符
    for (i=0; i<n; i++) {
        fgets(s[i], MAXSTR, stdin);
        len[i]=strlen(s[i]);
        s[i][len[i]--]=0;
    }
    //获得最小字符串的长度
    for (i=1,min=len[0]; i<n; i++)
        if (len[i]<min) min=len[i];
    //最最后一个字符开始比较所以字符串是否都相同
    for (i=1; i<=min; i++) {
        flag=1;
        for (j=1; j<n; j++) {
            if (s[j][len[j]-i]!=s[0][len[0]-i]) {
                flag=0;
                break;
            }
        }
        if (flag==0) break;
        cnt++;
    }

    if (cnt==0) printf("nai");
    else printf("%s", &s[0][len[0]-cnt]);//注意这里取地址的技巧
}

//1、有一个用例不过，看了几遍代码没发现问题，最后发现是MAXSTR取少了一个
//2、还可以reverse之后从头比较，最后打印再reverse回来
int main(int argc, char *argv[])
{
   fun1();
}

