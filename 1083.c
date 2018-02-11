#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSTR 11

typedef struct {
    char name[MAXSTR];
    char sub[MAXSTR];//subject
    int grade;
} Stu;

int cmp(const void *a, const void *b)
{
    Stu *x=(Stu *)a;
    Stu *y=(Stu *)b;
    return y->grade-x->grade;
}

void fun1()
{
    Stu *stu;
    int n, grade1, grade2;
    int i,j,cnt=0;
    scanf("%d", &n);
    stu=(Stu *)malloc(n*sizeof(stu[0]));
    for (i=0; i<n; i++)
        scanf("%s %s %d", stu[i].name, stu[i].sub, &stu[i].grade);
    scanf("%d%d", &grade1, &grade2);
    qsort(stu, n, sizeof(stu[0]), cmp);
    for (i=0; i<n; i++) {
        if (stu[i].grade>=grade1&&stu[i].grade<=grade2) {
            printf("%s %s\n", stu[i].name, stu[i].sub);
            cnt++;
        }
        else if (stu[i].grade<grade1) {
            break;//提前退出
        }
    }
    if (cnt==0) printf("NONE");
}

//数据大小不定本来想用cpp，想了下就是简单的排序还是用c来做了
int main(int argc, char *argv[])
{
   fun1();
}

