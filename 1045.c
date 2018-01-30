#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 201
#define MAXLEN 10000

void fun1()
{
    int map[MAX]={0};
    int dp[MAXLEN];
    int favor[MAX];
    int colors[MAXLEN];
    int n,m,len;
    int i,j,max=0;
    
    scanf("%d", &n);
    scanf("%d", &m);
    for (i=1; i<=m; i++) {
        scanf("%d", &favor[i]);
        //把对应颜色的map映射成它的下标，不光可以确定是否喜欢，还可快速查找
        map[favor[i]]=i;
    }
    
    scanf("%d", &len);
    for (i=0; i<len; i++)
        scanf("%d", &colors[i]);

    for (i=0,j=0; i<len;)//去掉不喜欢的颜色,也可以在存入不在喜欢的里面不存入
        if (map[colors[i]]==0) i++;
        else colors[j++]=colors[i++];
    len=j;
    
    dp[0]=len>0?1:0;//第一个只要存在就是1
    for (i=1; i<len; i++) {
        dp[i]=1;//去除了不喜欢的，是喜欢的最少也是1
        for (j=i-1; j>=0; j--) {
            if (map[colors[j]]<=map[colors[i]])
                dp[i]=dp[j]+1>dp[i]?dp[j]+1:dp[i];
        }
    }
    for (i=0; i<len; i++)
        max=dp[i]>max?dp[i]:max;
    printf("%d", max);
}

//1、这题技巧挺重要的，最重要的就是映射喜欢颜色对应的下标，
//既可以快速判断一种颜色是否是喜欢的颜色，也可以快速判别两种喜欢颜色的先后顺序
//2、dp的状态转移要判断当前喜欢颜色前所有颜色，因为有间隔
int main(int argc, char *argv[])
{
    fun1();
}
