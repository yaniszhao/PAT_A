#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000000

int CountOne(int n)
{
    char s[11];
    int i,cnt=0;
    sprintf(s, "%d", n);
    for (i=0; i<strlen(s); i++)
        if (s[i]=='1') cnt++;
    return cnt;
}

void fun1()
{//暴力破解，两个用例不过
    int n;
    int i,cnt=0;
    scanf("%d", &n);
    for (i=1; i<=n; i++)
        cnt+=CountOne(i);
    printf("%d", cnt);
}

//将每位上为1的个数相加，比如12，个位为1时十位可以为0、1就是2个，十位为1则个位为0、1、2即3个，总共为5个
//注意11在计算个位和计算十位的时候都出现，但是11有2个1，所以正好不用做处理
//当十位大于1时，如22，个位为1十位可以0、1、2即3个，个位取0-9即10个，共13个
//对某一位进行判断：
//1.当它为0时，要让其为1，左边可出现值为0~左边-1，即左值，右值可以取0~9...，即10^种；总共(左值)乘(10^位)
//2.为1时，要让其为1，左边可出现0~左值，即左值+1;右边可出现的值为0~右值，即右值+1；总共就是有(左值+1)乘(右值+1)
//3.大于1时，要让其为1，左边可以出现0~左值，即左值+1；右边可出现0~9...，即10^位种；总共就是有(左值+1)乘(10^位)
void fun2()
{//参考liuchuo的代码，有点难懂
    int n;
    int wei,now,left,right;
    int cnt=0;
    scanf("%d", &n);
    wei=1;//第一位是个位权
    while (n/wei) {
        left=n/wei/10;
        now=n/wei%10;
        right=n%wei;
        if (now==0) cnt+=left*wei;
        else if (now==1) cnt+=left*wei+right+1;//(left+1)*(right+1);
        else cnt+=(left+1)*wei;
        wei*=10;
    }
    printf("%d", cnt);
}

//暴力破解会超时
//第二种方法暂时还是有点不理解，后面再看看
int main(int argc, char *argv[])
{
    //fun1();
    fun2();
}

