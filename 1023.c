#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 22

void fun1()
{//long long也不够不能用这个
    char s[MAX];
    char flag[MAX]={0};
    int n;
    int i, ok=1;
    unsigned long long tmp;//因为有20位，long long也不够
    
    scanf("%s", s);
    
    n=(int)strlen(s);
    for (i=0; i<n; i++)
        flag[s[i]-'0']++;
    
    tmp=2*atoll(s);
    sprintf(s, "%lld", tmp);
    n=(int)strlen(s);
    for (i=0; i<n; i++)
        flag[s[i]-'0']--;
    
    for (i=0; i<10; i++)//不能用atoi(flag)否则好几个用例不过
        if (flag[i]!=0) {ok=0;break;}
    
    //if (atoi(flag)==0)
    if (ok)
        printf("Yes\n");
    else
        printf("No\n");
    printf("%s", s);
}

void fun2()
{
    char s[MAX];
    char s2[MAX];
    char flag[MAX]={0};
    int n;
    int i,j;
    int tmp, over=0;//只是乘2最多进位1
    int ok=1;
    
    scanf("%s", s);
    
    n=(int)strlen(s);
    for (i=0; i<n; i++)
        flag[s[i]-'0']++;
    
    //逆序存到s2;
    for (i=n-1, j=0; i>=0; i--, j++) {
        tmp=2*(s[i]-'0')+over;
        if (tmp>=10) {
            over=1;
            s2[j]=tmp-10+'0';
        }
        else {
            over=0;
            s2[j]=tmp+'0';
        }
    }
    
    for (i=0; i<j; i++)
        flag[s2[i]-'0']--;
    if (over) flag[1]--;
    
    for (i=0; i<10; i++)//不能用atoi(flag)否则好几个用例不过
        if (flag[i]!=0) {ok=0;break;}
    
    //if (atoi(flag)==0)
    if (ok)
        printf("Yes\n");
    else
        printf("No\n");
    
    if (over) printf("1");
    for (i=j-1; i>=0; i--)
        printf("%c", s2[i]);
}

void fun3()
{
    char s[MAX];
    char flag[MAX]={0};
    int n;
    int i;
    int tmp, over=0;//只是乘2最多进位1
    int ok=1;
    
    scanf("%s", s);
    
    n=(int)strlen(s);
    for (i=0; i<n; i++)
        flag[s[i]-'0']++;
    
    //逆序存到s2;
    for (i=n-1; i>=0; i--) {
        tmp=2*(s[i]-'0')+over;
        if (tmp>=10) {
            over=1;
            s[i]=tmp-10+'0';
        }
        else {
            over=0;
            s[i]=tmp+'0';
        }
    }
    
    for (i=0; i<n; i++)
        flag[s[i]-'0']--;
    if (over) flag[1]--;
    
    for (i=0; i<10; i++)//不能用atoi(flag)否则好几个用例不过
        if (flag[i]!=0) {ok=0;break;}
    
    //if (atoi(flag)==0)
    if (ok)
        printf("Yes\n");
    else
        printf("No\n");
    
    if (over) printf("1");
    printf("%s", s);
}

//因为有20位，用long long也表示不了，只能一位字符的处理
int main(int argc, char *argv[])
{
    //fun1();//数值存储
    //fun2();//逆序存储且额外空间
    fun3();//顺序存储且不占空间
}
