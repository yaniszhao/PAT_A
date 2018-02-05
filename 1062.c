#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100000

typedef struct {
    int no;
    int virtue;
    int talent;
    int total;
} Person;

//排序先按总成绩，再按virtue，最后按序号
int cmp(const void *a, const void *b)
{
    Person *x=(Person *)a;
    Person *y=(Person *)b;
    if (y->total!=x->total)
        return y->total-x->total;
    //y->total==x->total
    if (y->virtue==x->virtue)
        return x->no-y->no;
    else
        return y->virtue-x->virtue;
}

void fun1()
{
    Person sage[MAX];
    int scnt=0;
    Person noble[MAX];
    int ncnt=0;
    Person fool[MAX];
    int fcnt=0;
    Person rest[MAX];
    int rcnt=0;
    int n,low,high;
    int no, vir,tal;
    int i;

    scanf("%d%d%d", &n, &low, &high);
    for (i=0; i<n; i++) {
        scanf("%d%d%d", &no, &vir, &tal);
        if (vir>=high&&tal>=high) {//都>=high
            sage[scnt].no=no;
            sage[scnt].virtue=vir;
            sage[scnt].talent=tal;
            sage[scnt].total=vir+tal;
            scnt++;
        }
        else if (vir>=high&&tal>=low) {//vir>=hight;high>tal>=low
            noble[ncnt].no=no;
            noble[ncnt].virtue=vir;
            noble[ncnt].talent=tal;
            noble[ncnt].total=vir+tal;
            ncnt++;
        }
        else if (vir>=low&&tal>=low) {//high>vir>=low;high>tal>=low
            if (vir>=tal) {
                fool[fcnt].no=no;
                fool[fcnt].virtue=vir;
                fool[fcnt].talent=tal;
                fool[fcnt].total=vir+tal;
                fcnt++;
            }
            else {
                rest[rcnt].no=no;
                rest[rcnt].virtue=vir;
                rest[rcnt].talent=tal;
                rest[rcnt].total=vir+tal;
                rcnt++;
            }
        }
    }

    qsort(sage, scnt, sizeof(Person), cmp);
    qsort(noble, ncnt, sizeof(Person), cmp);
    qsort(fool, fcnt, sizeof(Person), cmp);
    qsort(rest, rcnt, sizeof(Person), cmp);
    printf("%d\n", scnt+ncnt+fcnt+rcnt);
    for (i=0; i<scnt; i++)
        printf("%08d %d %d\n", sage[i].no, sage[i].virtue, sage[i].talent);
    for (i=0; i<ncnt; i++)
            printf("%08d %d %d\n", noble[i].no, noble[i].virtue, noble[i].talent);
    for (i=0; i<fcnt; i++)
            printf("%08d %d %d\n", fool[i].no, fool[i].virtue, fool[i].talent);
    for (i=0; i<rcnt; i++)
                printf("%08d %d %d\n", rest[i].no, rest[i].virtue, rest[i].talent);
}

//分类要注意，进入排序的都是两个成绩都>=low的
//这道题分开排序好点，就是重复代码太多了
//排序先按总成绩，再按virtue，最后按序号
int main(int argc, char *argv[])
{
   fun1();
}

