#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10002//fgets还有个换行符，所以10001有个用例不过
#define MAXASCII 128

void fun1()
{
    int map[MAXASCII]={0};
    char s1[MAX], s2[MAX];
    int i,j,len;
    //不要用gets，但fgets有个换行符
    fgets(s1, MAX, stdin);
    fgets(s2, MAX, stdin);
    
    len=(int)strlen(s2);
    s2[len-1]=s2[len-1]=='\n'?'\0':s2[len-1];//处理不处理其实没关系
    for (i=0; i<len; i++)
        map[s2[i]]++;
    
    len=(int)strlen(s1);
    s1[len-1]=s1[len-1]=='\n'?'\0':s1[len-1];//处理不处理其实没关系
    
    for (i=0,j=0; i<len;)
        if (map[s1[i]]>0) i++;
        else s1[j++]=s1[i++];
    s1[j]='\0';
    printf("%s", s1);
}

int main(int argc, char *argv[])
{
    fun1();
}

