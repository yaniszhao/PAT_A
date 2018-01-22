#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTIME 1e7//10000

void ConvertWithRadix(char s[], int v)
{
    int high, low;
//    low=v%13;
//    v=v/13;
//    high=v%13;
    low=v%13;
    high=v/13;
    s[0]=high>=10?'A'+high-10:high+'0';
    s[1]=low>=10?'A'+low-10:low+'0';
}

void fun1()
{
    int r,g,b;
    char rgb[7]={0};
    scanf("%d%d%d", &r, &g, &b);
    ConvertWithRadix(&rgb[0], r);
    ConvertWithRadix(&rgb[2], g);
    ConvertWithRadix(&rgb[4], b);
    printf("#%s", rgb);
}

void fun2()
{
    char table[]="0123456789ABC";
    int i, color;
    printf("#");
    for (i=0; i<3; i++) {
        scanf("%d", &color);
        printf("%c%c", table[color/13], table[color%13]);
    }
}

int main(int argc, char *argv[])
{//第二种还是挺不错的
    //fun1();
    fun2();
}
