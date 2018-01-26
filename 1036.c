#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAXSTR 11

typedef struct stStu {
    char name[MAXSTR];
    char id[MAXSTR];
    int grade;
} Stu;

int GetGrade(Stu stu[], int n, int gender)
{//gender:0-male,1=female
    int i, most=0;
    for (i=1; i<n; i++) {
        if (gender==0) {
            if (stu[i].grade<stu[most].grade) most=i;
        }
        else {
            if (stu[i].grade>stu[most].grade) most=i;
        }
    }
    printf("%s %s\n", stu[most].name, stu[most].id);
    return stu[most].grade;
}

void fun1()
{
    Stu mstu[MAX];
    Stu fstu[MAX];
    int mnum=0, fnum=0;
    int mmin=-1, fmax=-1;
    int n;
    int i;
    char name[MAXSTR], gender;
    
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s %c", name, &gender);
        if (gender=='M') {
            memcpy(mstu[mnum].name, name, MAXSTR);
            scanf("%s %d", mstu[mnum].id, &mstu[mnum].grade);
            mnum++;
        }
        else {
            memcpy(fstu[fnum].name, name, MAXSTR);
            scanf("%s %d", fstu[fnum].id, &fstu[fnum].grade);
            fnum++;
        }
    }
    
    if (fnum==0) printf("Absent\n");
    else fmax=GetGrade(fstu, fnum, 1);
    
    if (mnum==0) printf("Absent\n");
    else mmin=GetGrade(mstu, mnum, 0);
    
    if (mmin==-1 || fmax==-1) printf("NA");
    else printf("%d", fmax-mmin);
}


int main(int argc, char *argv[])
{
    fun1();
}
