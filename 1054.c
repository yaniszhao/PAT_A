#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (16*1024*1024)//2^24可以用1<<24表示
#define MAXM 800
#define MAXN 600

void fun1()
{//内存超限，可以用stl的map来映射
    int *map;
    int m,n;
    int i,j,t, max=0;
    scanf("%d%d", &m, &n);
    map=(int *)malloc(MAX*sizeof(*map));
    memset(map, 0, MAX*sizeof(*map));
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d", &t);
            map[t]++;
        }
    }
    for (i=1; i<MAX; i++)
        max=(map[i]>map[max])?i:max;
    printf("%d", max);
}

//=========================================
int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

void fun2()
{//因为个数大于一半，所以总元素/2下标的那个数肯定就是要求的值
    int arr[MAXM*MAXN];
    int m,n;
    int i,j,cnt=0;
    scanf("%d%d", &m, &n);
    //arr=(int *)malloc(MAXM*MAXN*sizeof(*arr));
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d", &arr[cnt++]);
        }
    }
    qsort(arr, m*n, sizeof(arr[0]), cmp);
    printf("%d", arr[m*n/2]);
}

//=========================================
void fun3()
{//大于一半的值，怎么消都不会被消完
    int m,n;
    int i,j,t;
    int main=-1,cnt=0;
    scanf("%d%d", &m, &n);

    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d", &t);
            if (main==t) cnt++;
            else {
                if (cnt==0) {main=t; cnt++;}
                else cnt--;
            }
        }
    }
    printf("%d", main);
}

//1、直接用空间hash映射值的话，内存会超限，可以用stl的map来映射
//c非要映射也可以，把已经出现的放到一个数组a里，并用另一个对应的数组b存次数
//每次加数据的时候判断是否已经在数组a里了，是的话b里的值直接加1，否则加入a，b置1
//2、改用排序求中间的那个值即为所求的
//3、参考王道主元素的求法
int main(int argc, char *argv[])
{
    //fun1();
    //fun2();
    fun3();
}

