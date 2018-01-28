#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MAXVAL 10001

void fun1()
{
    int  map[MAXVAL]={0};
    int bets[MAX];
    int n;
    int i, win=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &bets[i]);
        map[bets[i]]++;
    }
    
    for (i=0; i<n; i++) {
        if (map[bets[i]]==1) {
            win=bets[i];
            break;
        }
    }
    if (win>0) printf("%d", win);
    else printf("None");
}

void fun2()
{//不用map，用两个循环也可以

}

//空间换时间还是好用
int main(int argc, char *argv[])
{
    fun1();
}


