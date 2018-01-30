#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCOUR 2501
#define MAX_STU_PER_COUR 400
#define INF 1e7

int NameToInt(char name[5])
{
    return (name[0]-'A')*26*26*10 + (name[1]-'A')*26*10 + \
            (name[2]-'A')*10 + (name[3]-'0');
}

void IntToName(int n, char name[5])
{
    name[0]=n/(26*26*10)+'A'; n=n%(26*26*10);
    name[1]=n/(26*10)+'A'; n=n%(26*10);
    name[2]=n/(10)+'A'; n=n%(10);
    name[3]=n+'0';
    name[4]='\0';
}

int cmp(const void *a, const void *b)
{
    return *((int*)a)>*((int*)b);
}

void fun1()
{
    int courses[MAXCOUR][MAX_STU_PER_COUR];
    int cnt[MAXCOUR]={0};
    int n,k;
    int i,j,num,index;
    char name[5];
    int token;
    scanf("%d%d", &n, &k);
    for (i=0; i<n; i++) {
        scanf("%s %d", name, &num);
        token=NameToInt(name);
        for (j=0; j<num; j++) {
            scanf("%d", &index);
            courses[index][cnt[index]++]=token;
        }
        
    }
    
    for (i=1; i<=k; i++) {
        printf("%d %d\n", i, cnt[i]);
        qsort(courses[i], cnt[i], sizeof(courses[0][0]), cmp);
        for (j=0; j<cnt[i]; j++) {
            IntToName(courses[i][j], name);
            printf("%s\n", name);
        }
    }
}

void fun2()
{//开组数组存名字，couses[][]存名字数组的下标省去了名字的转换
    
}

//1、最主要的就是按课程存储数据，另外把名字转成整形存储方便很多
//2、名字转整形和反转的函数要熟悉
//3、注意输出名字要按从小到到顺序，所以要排序
//4、MAX_STU_PER_COUR要开得足够大，否则最后一个用例不过，300-400之间某个点是临界点
//5、fun2要简单很多
int main(int argc, char *argv[])
{
    fun1();
}
