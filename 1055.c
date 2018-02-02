#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MAXQUE 1000
#define MAXNAME 9

typedef struct {
    char name[MAXNAME];
    int age;
    int worth;
} Person;

typedef struct {
    int max_num;
    int st_age;
    int ed_age;
} Query;

int cmp(const void *a, const void *b)
{//排序要计较3个值，不是简单比较worth
    Person *x=(Person *)a;
    Person *y=(Person *)b;
    if(y->worth!=x->worth)
        return y->worth-x->worth;
    else if (x->age!=y->age)
        return x->age-y->age;
    else
        return strcmp(x->name, y->name);

}

void fun1()
{
    Person per[MAX];
    Query que[MAXQUE];
    int n,k;
    int i,j,cnt;
    scanf("%d%d", &n, &k);
    for (i=0; i<n; i++)
        scanf("%s %d %d", per[i].name, &per[i].age, &per[i].worth);
    for (i=0; i<k; i++)
        scanf("%d%d%d", &que[i].max_num, &que[i].st_age, &que[i].ed_age);

    qsort(per, n, sizeof(per[0]), cmp);
    for (i=0; i<k; i++) {//如果在这个循环内得到每一次que[i]的话，可以不用que数组
        printf("Case #%d:\n", i+1);
        for (j=0,cnt=0; j<n && cnt<que[i].max_num; j++) {
            if (per[j].age>=que[i].st_age && per[j].age<=que[i].ed_age) {
                printf("%s %d %d\n", per[j].name, per[j].age, per[j].worth);
                cnt++;
            }
        }
        if (cnt==0) printf("None");
    }
}

void fun2()
{
    Person per[MAX];
    int n,k;
    int i,j,cnt;
    int max_num, st_age, ed_age;
    scanf("%d%d", &n, &k);
    for (i=0; i<n; i++)
        scanf("%s %d %d", per[i].name, &per[i].age, &per[i].worth);

    qsort(per, n, sizeof(per[0]), cmp);
    for (i=0; i<k; i++) {//如果在这个循环内得到每一次que[i]的话，可以不用que数组
        printf("Case #%d:\n", i+1);
        scanf("%d%d%d", &max_num, &st_age, &ed_age);
        for (j=0,cnt=0; j<n && cnt<max_num; j++) {
            if (per[j].age>=st_age && per[j].age<=ed_age) {
                printf("%s %d %d\n", per[j].name, per[j].age, per[j].worth);
                cnt++;
            }
        }
        if (cnt==0) printf("None");
    }
}

//注意排序要比较三个值，不是只是财富大小
//fun2只是比fun1节省了que[MAXQUE]的空间
int main(int argc, char *argv[])
{
   //fun1();
    fun2();
}

