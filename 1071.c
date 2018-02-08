#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSTR 1048576
#define MAXWORD 10000
#define MAX 1048576

typedef struct {
    char word[MAX+1];
    int cnt;
} Word;

char s[MAXSTR+1];
Word *words[MAXWORD];
int num=0;
char word[MAX+1];

int IsChar(char c)
{
    switch (c) {
        case '0'...'9':
        case 'a'...'z':
        case 'A'...'Z': return 1;
        default: return 0;
    }
}

char* GetWord(char *p)
{
    int i=0;
    for (; *p!='\0'&&!IsChar(*p); p++);
    if (*p=='\0') {word[i]=0; return p;}
    for (; IsChar(*p); p++)
        word[i++]=*p;
    word[i]=0;
    return p;
}

int IsInWords(char *word)
{
    int i;
    for (i=0; i<num; i++)
        if (strcmp(words[i]->word, word)==0)
            return i;
    return -1;
}

int cmp(const void *a, const void *b)
{
    Word *x=(Word *)a;
    Word *y=(Word *)b;
    return y->cnt-x->cnt;
}

void fun1()
{
    char *p=s;
    int i,index,max;
    fgets(s, MAXSTR, stdin);
    s[strlen(s)]='\0'; ;
    //for (p=s; *p!=0&&*p!='\"'; p++);//"前面的没用
    p=GetWord(p);
    while (word[0]!=0) {
        for (i=0; i<strlen(word); i++)//大写变小写
            if (word[i]<97&&word[i]>=65)//不要变数字
                word[i]=word[i]+32;
        index=IsInWords(word);
        if (index>-1)
            words[index]->cnt++;
        else {
            words[num]=(Word *)malloc(sizeof(Word));
            memcpy(words[num]->word, word, strlen(word)+1);
            words[num]->cnt=1;
            num++;
        }

        p=GetWord(p);
    }
//    qsort(words, num, sizeof(words[0]), cmp);
//    printf("%s %d", words[0].word, words[0].cnt);
    for (max=0,i=1; i<num; i++)
        if (words[i]->cnt>words[max]->cnt)
            max=i;
    printf("%s %d", words[max]->word, words[max]->cnt);
}

//1、大写转小写的时候时候注意别把数字的范围带进去了
//2、有的测试用例可能没有\"别去\"
//3、直接开数据太大了PAT会编译出错，要用动态数组，但是最后还是有一个用例超时，改用cpp吧
//4、这道题还是适合cpp来做，map省去Word类型，还可以直接用大小写转换函数和字符判断函数
int main(int argc, char *argv[])
{
   fun1();
}

