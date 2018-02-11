#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 11

char *mapnum[]={"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
char *mapwei[]={"Yi", "Qian", "Bai", "Shi", "Wan", "Qian", "Bai", "Shi"};
void fun1()
{
    char s[11];
    char s1[10];
    int i, j, start=0;
    int flag=0;
    scanf("%s", s);
    if (s[0]=='-') {printf("Fu "); start=1;}//处理负号
    //s1存的固定9个数，前面没有的填成0
    for (i=strlen(s)-1,j=8; i>=start; i--,j--) s1[j]=s[i];
    for (; j>=0; j--) s1[j]='0';
    //处理第一个非0数字，因为打印空格的关系
    for (i=0; s1[i]=='0'; i++);
    if (i==9) {printf("ling"); return;}//值就是0
    else if (i==8) {printf("%s", mapnum[s1[i]-'0']); return;}//只有个位
    else printf("%s %s", mapnum[s1[i]-'0'], mapwei[i]);
    //处理剩余的数字
    for (i++; i<=8; i++) {
        if (i==4) {//万位非常奇特它本身为0前面有值还是要打印
            if (s1[i]=='0') printf(" Wan");//自身为0
            else {//自身不为0
                if (flag==1) {//前面有0
                    printf(" ling %s Wan", mapnum[s1[i]-'0']);
                    flag=0;
                }
                else printf(" %s Wan", mapnum[s1[i]-'0']);
            }
        }
        else {
            if (s1[i]=='0') flag=1;//0标识
            else {
                if (flag==1) {
                    if (i==8) printf(" ling %s", mapnum[s1[i]-'0']);//处理个位
                    else printf(" ling %s %s", mapnum[s1[i]-'0'], mapwei[i]);
                    flag=0;
                }
                else {
                    if (i==8) printf(" %s", mapnum[s1[i]-'0']);//处理个位
                    else printf(" %s %s", mapnum[s1[i]-'0'], mapwei[i]);
                }
            }
        }
    }
}

//这道题最多只有九位，直接暴力破解了
//最主要就是万位的处理和中间有0的处理
int main(int argc, char *argv[])
{
   fun1();
}

