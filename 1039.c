#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40000
#define MAXCOURSE 2501
#define MAXREGSTU 200
#define MAXNAME 5

int IsStuInCourse(char course[MAXREGSTU*MAXNAME], int n, char name[MAXNAME])
{
    int i;
    for (i=0; i<n; i++)
        if (strcmp(&course[i*MAXNAME], name)==0) return 1;
    return 0;
}

void fun1()
{//最后一个用例超时
    char query[MAX][MAXNAME];
    char course[MAXCOURSE][MAXREGSTU*MAXNAME];
    int cnt[MAXCOURSE]={0};
    int regcourse[MAXCOURSE];
    int n,k;
    int i,j;
    int idx, num;
    scanf("%d%d", &n, &k);
    for (i=0; i<k; i++) {
        scanf("%d %d", &idx, &num);//课程的下标是从1开始的
        for (j=0; j<num; j++)
            scanf(" %s", &course[idx][j*MAXNAME]);
        cnt[idx]=num;
    }
    for (i=0; i<n; i++) {//查询人员下标从0开始
        scanf(" %s", query[i]);
    }
    
    for (i=0; i<n; i++) {
        printf("%s", query[i]);
        num=0;
        for (j=1; j<MAXCOURSE; j++)
            if (IsStuInCourse(course[j], cnt[j], query[i]))
                regcourse[num++]=j;
        printf(" %d", num);
        for (j=0; j<num; j++)
            printf(" %d", regcourse[j]);
        putchar('\n');
    }
}

void fun2()
{//把姓名变成序号，然后把对应的课放在对应的空间里面，最后只需要遍历打印即可

}

//1、要处理字符串，还要在对应字符串存储不止一个的数值，用c写比较麻烦了，还是推荐cpp
//2、cpp直接map加string加set就只有一个用例超时，想不超时则用hash
int main(int argc, char *argv[])
{
    fun1();
}

