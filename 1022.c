#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 10000
#define MAXSTR 81
#define MAXKEYSTR 55
#define MAXQUERY 1000

enum enType {
    TITLE=1,
    AUTHOR,
    KEY,
    PUBLISHER,
    YEAR
};

typedef struct stInfo {
    int id;
    char *title;
    char *author;
    char *keys;
    char *publisher;
    int year;
} Info;

void SortInfo(Info info[], int n)
{
    int i,j,min;
    Info tmp;
    for (i=0; i<n-1; i++) {
        min=i;
        for (j=i+1; j<n; j++)
            if (info[j].id<info[min].id) min=j;
        memcpy(&tmp, &info[i], sizeof(info[0]));
        memcpy(&info[i], &info[min], sizeof(info[0]));
        memcpy(&info[min], &tmp, sizeof(info[0]));
    }
}

void QueryWithTitle(Info info[], int n, char *title)
{
    int i, cnt=0;
    for (i=0; i<n; i++) {
        if (strcmp(info[i].title, title)==0) {
            printf("%d\n", info[i].id);
            cnt++;
        }
    }
    if (cnt==0) printf("Not Found\n");
}


void QueryWithAuthor(Info info[], int n, char *author)
{
    int i, cnt=0;
    for (i=0; i<n; i++) {
        if (strcmp(info[i].author, author)==0) {
            printf("%d\n", info[i].id);
            cnt++;
        }
    }
    if (cnt==0) printf("Not Found\n");
}

void QueryWithKey(Info info[], int n, char *key)
{
    int i, cnt=0;
    char *onekey;
    for (i=0; i<n; i++) {
        onekey=strtok(info[i].keys, " ");
        while (onekey) {
            if (strcmp(onekey, key)==0) {
                printf("%d\n", info[i].id);
                cnt++;
                break;
            }
            onekey=strtok(NULL, " ");
        }
    }
    if (cnt==0) printf("Not Found\n");
}

void QueryWithPublisher(Info info[], int n, char *pub)
{
    int i, cnt=0;
    for (i=0; i<n; i++) {
        if (strcmp(info[i].publisher, pub)==0) {
            printf("%d\n", info[i].id);
            cnt++;
        }
    }
    if (cnt==0) printf("Not Found\n");
}

void QueryWithYear(Info info[], int n, char *year)
{
    int i, cnt=0;
    for (i=0; i<n; i++) {
        if (info[i].year==atoi(year)) {
            printf("%d\n", info[i].id);
            cnt++;
        }
    }
    if (cnt==0) printf("Not Found\n");
    
}

void fun1()
{
    int n,m;
    Info *info;
    char *str;
    char *keystr;
    int queryid[MAXQUERY];
    char* querystr[MAXQUERY];
    int i;
    
    scanf("%d", &n);
    info=(Info *)malloc(n*sizeof(*info));
    for (i=0; i<n; i++) {
        scanf("%d\n", &info[i].id);//加\n或getchar吸收换行，否则后面字符串接收有问题
        
        str=(char *)malloc(MAXSTR);
        gets(str);
        info[i].title=str;
        
        str=(char *)malloc(MAXSTR);
        gets(str);
        info[i].author=str;
        
        keystr=(char *)malloc(MAXKEYSTR);
        gets(keystr);
        info[i].keys=keystr;
        
        str=(char *)malloc(MAXSTR);
        gets(str);
        info[i].publisher=str;
        
        //加\n或getchar吸收换行，否则后面字符串接收有问题
        scanf("%d", &info[i].year);getchar();
    }
    
    scanf("%d", &m);
    for (i=0; i<m; i++) {
        scanf("%d: ", &queryid[i]);
        
        str=(char *)malloc(MAXSTR);
        gets(str);
        querystr[i]=str;
    }
    
    SortInfo(info, n);
    
    for (i=0; i<m; i++) {
        switch (queryid[i]) {
            case TITLE:
                printf("%d: %s\n", queryid[i], querystr[i]);
                QueryWithTitle(info, n, querystr[i]);
                break;
            case AUTHOR:
                printf("%d: %s\n", queryid[i], querystr[i]);
                QueryWithAuthor(info, n, querystr[i]);
                break;
            case KEY:
                printf("%d: %s\n", queryid[i], querystr[i]);
                QueryWithKey(info, n, querystr[i]);
                break;
            case PUBLISHER:
                printf("%d: %s\n", queryid[i], querystr[i]);
                QueryWithPublisher(info, n, querystr[i]);
                break;
            case YEAR:
                printf("%d: %s\n", queryid[i], querystr[i]);
                QueryWithYear(info, n, querystr[i]);
                break;
        }
    }
    
    //最后该free按理说要free，但是这种程序不free也没问题
}

int main(int argc, char *argv[])
{
    fun1();
}
