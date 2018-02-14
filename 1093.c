#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100001

void fun1()
{
    char s[MAX];
    int pcnt[MAX]={0}, tcnt[MAX]={0}, cnt=0;
    int i, len;

    scanf("%s", s);
    len=strlen(s);
    //每个位置及前面P的个数
    if (s[0]=='P') pcnt[0]++;
    for (i=1; i<len; i++)
        pcnt[i]=s[i]=='P'?pcnt[i]=pcnt[i-1]+1:pcnt[i-1];
    //每个位置及后面T的个数
    if (s[len-1]=='T') tcnt[len-1]++;
    for (i=len-2; i>=0; i--)
        tcnt[i]=s[i]=='T'?tcnt[i]=tcnt[i+1]+1:tcnt[i+1];
    //注意要两次求模
    for (i=1; i<len-1; i++)
        if (s[i]=='A') cnt+=pcnt[i-1]*tcnt[i+1];//cnt=(cnt+(pcnt[i-1]*tcnt[i+1])%1000000007)%1000000007;

    printf("%d", cnt%1000000007);
}

//1、如果直接暴力破解先匹配P再匹配A和T很麻烦
//2、如果找到A然后求左边P的个数和右边T的个数时间复杂度是O(n^2)会超时，
//想到dp里用数组记录状态的例子，所以用2个数组记录下P和T在每个位置的状态，空间换时间
//3、考虑值较大时要除以一个大的质数1000000007，注意这里要除2次
//4、可以参考liuchuo的代码，先记录tcnt,然后P和A一起循环可以少一个循环
int main(int argc, char *argv[])
{
   fun1();
}

