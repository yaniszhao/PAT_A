#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000

void fun1()
{
    int map[128];
    char *week[7]={"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    char s1[MAX], s2[MAX], s3[MAX], s4[MAX];
    int day, hour, mins;
    int i,j,len;
    char c;

    //initialize map
    for (c='0'; c<='9'; c++) map[c]=c-'0';
    for (c='A'; c<='N'; c++) map[c]=c-'A'+10;

    scanf("%s%s%s%s", s1, s2, s3, s4);

    len = (i=strlen(s1)) < (j=strlen(s2)) ? i : j;
    //即使相等，但不属于A-G的话还是循环，注意里面判断的写法
    //for (i=0; i<len&&(s1[i]!=s2[i]||(s1[i]<'A'||s1[i]>'G')); i++);
    for (i=0; i<len; i++)
        if (s1[i]==s2[i]&&(s1[i]>='A'&&s1[i]<='G'))
            break;
    day=s1[i]-'A';
    for (i=i+1; i<len; i++)
        if (s1[i]==s2[i]&&((s1[i]>='0'&&s1[i]<='9')||(s1[i]>='A'&&s1[i]<='N')))
            break;
    hour=map[s1[i]];

    len = (i=strlen(s3)) < (j=strlen(s4)) ? i : j;
    //len=strlen(s3)<strlen(s4)?strlen(s3):strlen(s4);
    //for (i=0; i<len&&(s3[i]!=s4[i]||(s3[i]<'a'||s3[i]>'z')); i++);
    for (i=0; i<len; i++)//要注意大小写都要包括
        if (s3[i]==s4[i]&&(s3[i]>='a'&&s3[i]<='z')||(s3[i]>='A'&&s3[i]<='Z'))
            break;
    mins=i;

    printf("%s %02d:%02d", week[day], hour, mins);
}

//1、开始SAT写成了STA好多用例都没过
//2、注意最后一个不光有小写字母还包括大写字母
//3、注意for循环里写的格式，简单的判断可以写在里面，复杂的还是单独写
int main(int argc, char *argv[])
{
   fun1();
}

