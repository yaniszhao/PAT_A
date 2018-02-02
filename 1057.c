#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

int stk[MAX], top=-1;
int bak[MAX];


int cmp(const void *a, const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}

//key肯定是正整数，栈为空返回0
int PeekMedian()
{
    if (top==-1) return 0;
    memcpy(bak, stk, (top+1)*sizeof(stk[0]));
    qsort(bak, top+1, sizeof(bak[0]), cmp);
    return bak[top/2];
}

//当栈满，返回0
int Push(int val)
{
    if (top==MAX-1) return 0;
    stk[++top]=val;
    return val;
}

//当栈空，返回0
int Pop()
{
    if (top==-1) return 0;
    return stk[top--];
}

//额外数组，每次取值前先排序
void fun1()
{
    char opt[11];//最长的命令PeekMedian为10个字符

    int n;
    int i,val,ans;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", opt);
        if (opt[1]=='e') {//PeekMedian
            ans=PeekMedian();
            if (ans==0) printf("Invalid\n");
            else printf("%d\n", ans);
        }
        else if (opt[1]=='u') {//Push
            scanf("%d", &val);
            ans=Push(val);
            if (ans==0) printf("Invalid\n");
        }
        else {//Pop
            ans=Pop();
            if (ans==0) printf("Invalid\n");
            else printf("%d\n", ans);
        }
    }
}
//==============================================
int map[MAX];
//key肯定是正整数，栈为空返回0
int PeekMedian2()
{
    int i=1, n=top/2+1;
    if (top==-1) return 0;
    for (i=0; i<MAX;) {
        if (map[i]==0) i++;
        else if (n>map[i]) {n=n-map[i]; i++;}
        else return i;
    }
    return 0;
}

//当栈满，返回0
int Push2(int val)
{
    if (top==MAX-1) return 0;
    stk[++top]=val;
    map[val]++;
    return val;
}

//当栈空，返回0
int Pop2()
{
    if (top==-1) return 0;
    map[stk[top]]--;
    return stk[top--];
}

//hash，额外数组，每个值对应一个空间存次数
void fun2()
{
    char opt[11];//最长的命令PeekMedian为10个字符
    int n;
    int i,val,ans;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
       scanf("%s", opt);
       if (opt[1]=='e') {//PeekMedian
           //ans=PeekMedian2();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
       else if (opt[1]=='u') {//Push
           scanf("%d", &val);
           ans=Push2(val);
           if (ans==0) printf("Invalid\n");
       }
       else {//Pop
           ans=Pop2();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
    }
}

//==============================================
void Insert(int val)
{
    int i=top;
    while (i>=0 && bak[i]>val) {
        bak[i+1]=bak[i];
        i--;
    }
    bak[i+1]=val;
}

void Remove(int val)
{
    int i;
    for (i=0; bak[i]!=val; i++);
    for (;i<top;i++) bak[i]=bak[i+1];
}

//key肯定是正整数，栈为空返回0
int PeekMedian3()
{
    if (top==-1) return 0;
    return bak[top/2];
}

//当栈满，返回0
int Push3(int val)
{
    if (top==MAX-1) return 0;
    Insert(val);
    stk[++top]=val;
    return val;
}

//当栈空，返回0
int Pop3()
{
    if (top==-1) return 0;
    Remove(stk[top]);
    return stk[top--];
}

//额外数组，每次插入保证有序
void fun3()
{
    char opt[11];//最长的命令PeekMedian为10个字符
    int n;
    int i,val,ans;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
       scanf("%s", opt);
       if (opt[1]=='e') {//PeekMedian
           ans=PeekMedian3();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
       else if (opt[1]=='u') {//Push
           scanf("%d", &val);
           ans=Push3(val);
           if (ans==0) printf("Invalid\n");
       }
       else {//Pop
           ans=Pop3();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
    }
}
//==============================================
#define lowbit(x) (x&-x)

void Update(int pos, int val)
{
    for (; pos<MAX; pos+=lowbit(pos))
        map[pos]+=val;
}

int GetSum(int pos)
{
    int sum=0;
    for (; pos>0; pos-=lowbit(pos))
        sum+=map[pos];
    return sum;
}

//key肯定是正整数，栈为空返回0
int PeekMedian4()
{
    int left=0, right=MAX, n=top/2+1;
    int sum,mid;
    if (top==-1) return 0;
    while (left<right) {//最后的时候left==right
        mid=(left+right)/2;
        sum=GetSum(mid);
//        if (sum==n)  return mid;
//        else if (sum>n) right=mid-1;
        if (sum>=n) right=mid;//可能有重复值的情况使得sum>n
        else left=mid+1;
    }
    return left;
}

//当栈满，返回0
int Push4(int val)
{
    if (top==MAX-1) return 0;
    stk[++top]=val;
    Update(val, 1);//数据+1
    return val;
}

//当栈空，返回0
int Pop4()
{
    if (top==-1) return 0;
    Update(stk[top], -1);
    return stk[top--];
}

void fun4()
{
    char opt[11];//最长的命令PeekMedian为10个字符
    int n;
    int i,val,ans;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
       scanf("%s", opt);
       if (opt[1]=='e') {//PeekMedian
           ans=PeekMedian4();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
       else if (opt[1]=='u') {//Push
           scanf("%d", &val);
           ans=Push4(val);
           if (ans==0) printf("Invalid\n");
       }
       else {//Pop
           ans=Pop4();
           if (ans==0) printf("Invalid\n");
           else printf("%d\n", ans);
       }
    }
}

//1、方法1和方法3都一样，查值前保证有序，然后根据下标取值
//2、方法2用的hash表，最后确定取第几大的值，然后遍历hash取值
//3、前3种方法本质上没什么区别，都有三个用例超时
//4、第4种方法模仿方法2用树状数组，通过计算个数2分得到结果
//方法2查询的复杂度是O(MAX),方法4二分乘求和即O(logn*logn),
//而且push和pop都还增加了update操作效率还比方法2高很多
int main(int argc, char *argv[])
{
   fun4();
}

