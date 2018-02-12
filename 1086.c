#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 30

int in[MAX], pre[MAX], post[MAX];
int incnt=0,precnt=0,postcnt=0;
int n;

void PreAndInToPost(int st1, int ed1, int st2, int ed2, int st3, int ed3)
{//如果嫌弃参数多了，可以都只传st然后传个len就只有4个参数，或者不传len通过pre[0]在in中得到
    int mid, len;
    if (st1>ed1) return;
    for (mid=st2; mid<=ed2&&in[mid]!=pre[st1]; mid++);
    post[ed3]=pre[st1];
    len=mid-st2;
    PreAndInToPost(st1+1, st1+len, st2, mid-1, st3, st3+len-1);
    PreAndInToPost(st1+len+1, ed1, mid+1, ed2, st3+len, ed3-1);
}

void fun1()
{
    int stk[MAX], top=-1;
    int i,val;
    char opt[5];
    scanf("%d", &n);
    for (i=0; i<2*n; i++) {
        scanf("%s", opt);
        if (opt[1]=='u') {
            scanf("%d", &val);
            stk[++top]=val;
            pre[precnt++]=val;
        }
        else {
            in[incnt++]=stk[top--];
        }
    }

    PreAndInToPost(0, n-1, 0, n-1, 0, n-1);
    if (n>0) printf("%d", post[0]);
    for (i=1; i<n; i++) printf(" %d", post[i]);
}

//就是简单的前序中序转后序，一次ac
//递归函数参数多但是好理解点，当然也可以减少些
int main(int argc, char *argv[])
{
   fun1();
}

