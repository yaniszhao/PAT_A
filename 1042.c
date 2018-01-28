#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 54

char *IntToStr(int n)
{
    static char s[4];
    switch (n/13) {
        case 0: s[0]='S'; break;
        case 1: s[0]='H'; break;
        case 2: s[0]='C'; break;
        case 3: s[0]='D'; break;
        case 4: s[0]='J'; break;
    }
    n=n%13;
    sprintf(&s[1], "%d", n+1);
    return s;
}

void fun1()
{
    int map1[MAX];
    int map2[MAX];
    int order[MAX];
    int k;
    int i, j;
    scanf("%d", &k);
    for (i=0; i<MAX; i++) scanf("%d", &order[i]);
    for (i=0; i<MAX; i++) map1[i]=i;
    do {
        for (j=0; j<MAX; j++)
            map2[order[j]-1]=map1[j];
        memcpy(map1, map2, MAX*sizeof(map1[0]));
    } while (--k>0);
    printf("%s", IntToStr(map1[0]));
    for (i=1; i<54; i++)
        printf(" %s", IntToStr(map1[i]));
}

int main(int argc, char *argv[])
{
    fun1();
}





