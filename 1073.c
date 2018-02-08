#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10000
#define INF 10000

void fun1()
{
    char cnum[MAX], cexp[MAX], c;
    int i,len,sign,iexp;

    scanf("%c", &c);
    if (c=='-') printf("%c", c);
    for (i=0; c!='E'; i++) {//c肯定为'+'或者'-'可以不用初始化
        scanf("%c", &c);
        cnum[i]=c=='E'?0:c;
    }

    scanf("%c", &c);
    sign=c=='-'?1:0;
    for (i=0; c!='\n'; i++) {//c肯定为'E'可以不用初始化
        scanf("%c", &c);
        cexp[i]=c=='\n'?0:c;
    }

    iexp=atoi(cexp);
    //指数为0打印原值，虽然这个没用用例
    if (iexp==0) {printf("%s", cnum); return;}

    if (sign==0) {
        putchar(cnum[0]);
        len=strlen(cnum);
        for (i=2; i<=len&&iexp>0; iexp--)
            if (cnum[i]==0) putchar('0');
            else {putchar(cnum[i]); i++;}
        if (cnum[i]!=0) putchar('.');
        while (cnum[i]!=0) putchar(cnum[i++]);
    }
    else {
        printf("0.");
        while (--iexp>0) putchar('0');
        for (i=0; i<strlen(cnum); i++)
            if (cnum[i]!='.') putchar(cnum[i]);
    }

    //这种方法当sign为负时cnum后面的0不会打印，为正时精度可能丢失
    //    fnum=atof(cnum);
    //    if (sign==0) printf("%.0f", fnum*pow(10,iexp));
    //    else printf("%.0f", fnum/pow(10,iexp));
}

//这题看起来简单，小细节还是不少啊
//当sign为负时cnum后面的0要保留
//当sign为正时用float类型小数后面的可能会有不干净的数
int main(int argc, char *argv[])
{
   fun1();
}

