#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

void fun1()
{
    int a[2],b[2],c[2];
    int x,y,z;
    int i, over=0;
    for (i=0; i<2; i++) scanf("%d.%d.%d", &a[i], &b[i], &c[i]);
    z=(c[0]+c[1])%29;
    over=(c[0]+c[1])/29;//c[0]+c[1]>=29?1:0;
    y=(b[0]+b[1]+over)%17;
    over=(b[0]+b[1]+over)/17;//记住要加over
    x=(a[0]+a[1]+over);
    //最后不会溢出，题目给定范围是为了确定数据类型
    //over=b[0]+b[1]+over>=17?1:0;
    printf("%d.%d.%d", x, y, z);
}

//1、注意y和x都要加over，开始我忘了加有个用例不过
//2、还可以把钱全部换成最小的，然后用/%得到结果
//3、基于我的方法根据是否大于边界值可以把%操作改成减法，/操作改成判断
int main(int argc, char *argv[])
{
   fun1();
}

