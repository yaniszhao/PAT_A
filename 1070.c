#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 1000

typedef struct {
    float ton;//这个地方要float,int有个用例不过
    float price;
    float rate;
} Moon;

int cmp(const void *a, const void *b)
{
    Moon *x=(Moon *)a;
    Moon *y=(Moon *)b;
    if (x->rate<y->rate) return 1;
    else return -1;
}

void fun1()
{
    Moon moon[MAX];
    int n,d;
    int i;
    float total=0;
    scanf("%d%d", &n, &d);
    for (i=0; i<n; i++) scanf("%f", &moon[i].ton);
    for (i=0; i<n; i++) {
        scanf("%f", &moon[i].price);
        //对除数做判断
        moon[i].rate=moon[i].ton!=0?moon[i].price/moon[i].ton:0;
    }
    qsort(moon, n, sizeof(Moon), cmp);
    for (i=0; i<n&&d>0; i++) {//i<n可以不要，最好加上
        if (moon[i].ton<=d) {
            total+=moon[i].price;
            d=d-moon[i].ton;
        }
        else {
            total+=d*moon[i].rate;
            d=0;
        }
    }
    printf("%.2lf", total);
}

//开始有个用例不过，把float换成double，判断除数是否为0，还是不能过
//后来以为是cmp问题，修改cmp函数和换成cpp代码都不能过
//最后发现是ton类型得是float,所以输入得ton可能是小数
int main(int argc, char *argv[])
{
   fun1();
}

