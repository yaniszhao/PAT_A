#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000

void fun1()
{
    int map[128]={0};
    char s1[MAX], s2[MAX];
    int need, extra=0;
    int i;
    scanf("%s %s", s1, s2);
    need=strlen(s2);
    for (i=0; i<need; i++) map[s2[i]]++;
    for (i=0; i<strlen(s1); i++) {
        if (map[s1[i]]>0) {
            map[s1[i]]--;
            need--;
        }
        else extra++;
    }

    if (need==0) printf("Yes %d", extra);
    else printf("No %d", need);
}

//简单题，就是hash的应用
int main(int argc, char *argv[])
{
   fun1();
}

