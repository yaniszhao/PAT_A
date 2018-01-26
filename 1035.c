#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define MAXSTR 11

typedef struct stUser {
    char name[MAXSTR];
    char psw[MAXSTR];
    int mflag;
} User;

void JudgeAndModify(User *u, int *cnt)
{
    char map1[4]="10lO";
    char map2[4]="@%Lo";
    int i,j,len;
    u->mflag=0;
    len=(int)strlen(u->psw);
    for (i=0; i<len; i++) {
        for (j=0; j<4; j++) {
            if (u->psw[i]==map1[j]) {
                u->psw[i]=map2[j];
                *cnt = u->mflag==0?*cnt+1:*cnt;
                u->mflag=1;
            }
        }
    }
}

void fun1()
{
    User user[MAX];
    int n;
    int i,cnt=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s %s", user[i].name, user[i].psw);
        JudgeAndModify(&user[i], &cnt);
    }
    
    if (cnt>0) {
        printf("%d\n", cnt);
        for (i=0; i<n; i++)
            if (user[i].mflag==1)
                printf("%s %s\n", user[i].name, user[i].psw);
    }
    else {//要考虑单复数, is/are, account/accounts
        if (n<=1) printf("There is %d account and no account is modified", n);
        else printf("There are %d accounts and no account is modified", n);
    }

}


int main(int argc, char *argv[])
{
    fun1();

}
