#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MAXNAME 9

typedef struct stStu {
    int id;
    char name[MAXNAME];
    int score;
} Stu;

enum ColType {
    ID=1,
    NAME,
    SCORE
};

void Sort(Stu stu[], int n, int c)
{
    int i,j,min;
    Stu t;
    for (i=0; i<n-1; i++) {
        min=i;
        for (j=i+1; j<n; j++) {
            switch (c) {
                case ID:
                    if (stu[j].id<stu[min].id)
                        min=j;
                    break;
                case NAME:
                    if (strcmp(stu[j].name, stu[min].name)<0)
                        min=j;
                    else if (strcmp(stu[j].name, stu[min].name)==0 && stu[j].id<stu[min].id)
                        min=j;
                    break;
                case SCORE:
                    if (stu[j].score<stu[min].score)
                        min=j;
                    else if (stu[j].score==stu[min].score && stu[j].id<stu[min].id)
                        min=j;
                    break;
            }
        }
        t=stu[i];
        stu[i]=stu[min];
        stu[min]=t;
//        memcpy(&t, &stu[i], sizeof(t));
//        memcpy(&stu[i], &stu[min], sizeof(t));
//        memcpy(&stu[min], &t, sizeof(t));
    }
    
}

int Partition(Stu stu[], int n, int c)
{
    int l=0, r=n-1;
    Stu s;
    s=stu[0];
    while (l<r) {
        while (l<r) {
            if (c==ID) {
                if (stu[r].id<s.id) {stu[l]=stu[r]; break;}
                else r--;
            }
            if (c==NAME) {
                if (strcmp(stu[r].name, s.name)<0 || \
                    (strcmp(stu[r].name, s.name)==0 && stu[r].id<s.id))
                    {stu[l]=stu[r]; break;}
                else r--;
            }
            if (c==SCORE) {
                if (stu[r].score<s.score || (stu[r].score==s.score && stu[r].id<s.id))
                    {stu[l]=stu[r]; break;}
                else r--;
            }
        }
        
        while (l<r) {
            if (c==ID) {
                if (stu[l].id>s.id) {stu[r]=stu[l]; break;}
                else l++;
            }
            if (c==NAME) {
                if (strcmp(stu[l].name, s.name)>0 || \
                    (strcmp(stu[l].name, s.name)==0 && stu[l].id>s.id))
                {stu[r]=stu[l]; break;}
                else l++;
            }
            if (c==SCORE) {
                if (stu[l].score>s.score || (stu[l].score==s.score && stu[l].id>s.id))
                {stu[r]=stu[l]; break;}
                else l++;
            }
        }
    }
    stu[l]=s;
    return  l;
}

void QuickSort(Stu stu[], int n, int c)
{
    int pivot;
    if (n<=0) return;
    pivot=Partition(stu, n, c);
    QuickSort(stu, pivot, c);//不是pivot-1因为pivot是下标
    QuickSort(&stu[pivot+1], n-pivot-1, c);
}

void fun1()
{
    int n,c;
    int i;
    Stu stu[MAX];
    scanf("%d%d", &n, &c);
    for (i=0; i<n; i++)
        scanf("%d %s %d", &stu[i].id, stu[i].name, &stu[i].score);
    QuickSort(stu, n, c);
    
    for (i=0; i<n; i++)
        printf("%06d %s %d\n", stu[i].id, stu[i].name, stu[i].score);
}

//要用快排，否则最后一个用例超时
int main(int argc, char *argv[])
{
    fun1();
}
