#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 81

void fun1()
{
    char map[128]={0};//0标识s2未出现过，1标识s2出现过，2标识s2未出现s1出现了
    char s1[MAX], s2[MAX];
    int i;
    scanf("%s %s", s1, s2);
    for (i=0; i<strlen(s2); i++) {
        if (s2[i]=='_') continue;
        if (s2[i]>='A'&&s2[i]<='Z') map[s2[i]+32]=1;
        else if (s2[i]>='a'&&s2[i]<='z') map[s2[i]-32]=1;
        map[s2[i]]=1;
    }
    
    for (i=0; i<strlen(s1); i++) {
        if (s1[i]=='_') continue;
        if (map[s1[i]==2]) continue;//已经排除了
        
        if (s1[i]>='0'&&s1[i]<='9'&&map[s1[i]]==0) {//数字
            putchar(s1[i]);
            map[s1[i]]=2;//标识排除
        }
        else if (s1[i]>='a'&&s1[i]<='z'&&map[s1[i]]==0) {
            putchar(s1[i]-32);//打印大写
            map[s1[i]]=map[s1[i]-32]=2;//大小写都标识排除
        }
        else if (s1[i]>='A'&&s1[i]<='Z'&&map[s1[i]]==0) {
            putchar(s1[i]);//打印自己
            map[s1[i]]=map[s1[i]+32]=2;//大小写都标识排除
        }
    }
}

void fun2()
{//用了几个函数，toupper,isdigit,isalpha
    int map[128]={0};
    int vis[128]={0};
    char s1[MAX], s2[MAX];
    int i;
    scanf("%s%s", s1, s2);
    
    for (i=0; i<strlen(s2); i++)
        if (isdigit(s2[i])) map[s2[i]]=1;
        else if (isalpha(s2[i])) map[toupper(s2[i])]=1;
    
    for (i=0; i<strlen(s1); i++)
        if (isdigit(s1[i]) && map[s1[i]]==0 && vis[s1[i]==0]) {
            putchar(s1[i]);
            vis[s1[i]]=1;
        }
        else if (isalpha(s1[i]) && map[toupper(s1[i])]==0 && vis[toupper(s1[i])]==0]){
            putchar(toupper(s1[i]));
            vis[toupper(s1[i])]=1;
        }
}

void fun3()
{//用了几个函数，toupper,isdigit,isalpha
    int map[128]={0};
    char s1[MAX], s2[MAX];
    int i;
    scanf("%s%s", s1, s2);
    
    for (i=0; i<strlen(s2); i++)
        if (isalpha(s2[i])) map[toupper(s2[i])]=1;
        else map[s2[i]]=1;
    
    for (i=0; i<strlen(s1); i++)
        if (isalpha(s1[i])) {
            if (map[toupper(s1[i])]==0) {
                putchar(toupper(s1[i]));
                map[toupper(s1[i])]=1;
            }
        }
        else {
            if (map[s1[i]]==0) {
                putchar(s1[i]);
                map[s1[i]]=1;
            }
        }
    
}

//fun1和fun2都没考虑'_'会坏的情况，有一个用例过不了
int main(int argc, char *argv[])
{
    fun3();
}

