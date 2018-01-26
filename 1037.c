#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
#define MAXSTR 11


int cmp(const void *a, const void *b)
{
    return *((int *)a)<*((int *)b);
}

int GetMaxPos(int arr[], int visit[], int n)
{
    int i;
    for (i=0; i<n; i++) {
        if (visit[i]==0 && arr[i]>0) return i;
        else if (arr[i]<=0) break;
    }
    return -1;
}

int GetMinNeg(int arr[], int visit[], int n)
{
    int i;
    for (i=n-1; i>=0; i--) {
        if (visit[i]==0 && arr[i]<0) return i;
        else if (arr[i]>=0) break;
    }
    return -1;
}

void fun1()
{//这种方法会超时
    int coupon[MAX], product[MAX];
    int cvisit[MAX]={0}, pvisit[MAX]={0};
    int nc,np;
    int i, tmp;
    int total=0;
    
    scanf("%d", &nc);
    for (i=0; i<nc; i++) scanf("%d", &coupon[i]);
    scanf("%d", &np);
    for (i=0; i<np; i++) scanf("%d", &product[i]);
    
    qsort(coupon, nc, sizeof(int), cmp);
    qsort(product, np, sizeof(int), cmp);
    
    for (i=0; i<nc; i++) {//处理较大的正数
        if (coupon[i]<0) break;
        tmp=GetMaxPos(product, pvisit, np);
        if (tmp==-1) break;
        else {
            total+=coupon[i]*product[tmp];
            cvisit[i]=pvisit[tmp]=1;
        }
    }
    
    for (i=nc-1; i>=0; i--) {//处理小的负数
        if (coupon[i]>0) break;
        tmp=GetMinNeg(product, pvisit, np);
        if (tmp==-1) break;
        else {
            total+=coupon[i]*product[tmp];
            cvisit[i]=pvisit[tmp]=1;
        }
    }
    
    //还剩下 (c正<p正 或 c正<p正) 或 (c负<p负 或 c负<p负)
    printf("%d", total);
}

//=====================================================

void fun2()
{//想到只加相同符号的，所以截取
    int coupon[MAX], product[MAX];
    int nc,np;
    int ncpos=0, ncneg=0, nppos=0, npneg=0;
    int npos, nneg;
    int i;
    int total=0;
    
    scanf("%d", &nc);
    for (i=0; i<nc; i++) {
        scanf("%d", &coupon[i]);
        if (coupon[i]>0) ncpos++;
        else if (coupon[i]<0) ncneg++;
    }
    
    scanf("%d", &np);
    for (i=0; i<np; i++) {
        scanf("%d", &product[i]);
        if (product[i]>0) nppos++;
        else if (product[i]<0) npneg++;
    }
    
    qsort(coupon, nc, sizeof(int), cmp);
    qsort(product, np, sizeof(int), cmp);
    
    npos=ncpos;
    nneg=ncneg;
    if (ncpos>nppos && ncneg>npneg) {
        for (i=0; i<npneg; i++)
            coupon[nppos+i]=coupon[ncpos+ncneg-npneg+i];
        npos=nppos;
        nneg=npneg;
    }
    else if (ncpos>nppos && ncneg<npneg) {
        for (i=0; i<ncneg; i++)
            coupon[nppos+i]=coupon[nc-ncneg+i];
        for (i=0; i<ncneg; i++)
            product[nppos+i]=product[np-ncneg+i];
        npos=nppos;
        nneg=ncneg;
    }
    else if (ncpos<nppos && ncneg>npneg) {
        for (i=0; i<npneg; i++)
            coupon[ncpos+i]=coupon[nc-npneg+i];
        for (i=0; i<npneg; i++)
            product[ncpos+i]=product[np-npneg+i];
        npos=ncpos;
        nneg=npneg;
    }
    else if (ncpos<nppos && ncneg<npneg) {
        for (i=0; i<ncneg; i++)
            product[ncpos+i]=product[np-ncneg+i];
        npos=ncpos;
        nneg=ncneg;
    }
    
    for (i=0; i<npos; i++) {//处理较大的正数
        total+=coupon[i]*product[i];
    }
    
    for (i=0; i<nneg; i++) {//处理小的负数
        total+=coupon[npos+i]*product[npos+i];
    }
    
    printf("%d", total);
}
//==================================================
void fun3()
{//再考虑了下根本不用截取
    int coupon[MAX], product[MAX];
    int nc,np;
    int i,j;
    int total=0;
    
    scanf("%d", &nc);
    for (i=0; i<nc; i++) {
        scanf("%d", &coupon[i]);
    }
    
    scanf("%d", &np);
    for (i=0; i<np; i++) {
        scanf("%d", &product[i]);
    }
    
    qsort(coupon, nc, sizeof(int), cmp);
    qsort(product, np, sizeof(int), cmp);
    

    
    for (i=0; i<nc && i<np; i++) {//处理较大的正数
        if (coupon[i]<0 || product[i]<0) break;
        total+=coupon[i]*product[i];
    }
    
    for (i=nc-1, j=np-1; i>=0&&j>=0; i--, j--) {//处理小的负数
        if (coupon[i]>0 || product[j]>0) break;
        total+=coupon[i]*product[j];
    }
    
    printf("%d", total);
}

int main(int argc, char *argv[])
{
    //fun1();
    //fun2();
    fun3();
}
