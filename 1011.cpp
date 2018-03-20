#include <iostream>
#include <algorithm>
#include <strstream>
#include <iomanip>
#include <vector>
using namespace std;

//char map[]={'W', 'T', 'L'};
char map[]={"WTL"};//map大小是4

void fun1()
{
    int maxidx;
    float product=1.0, maxval, val;
    for (int i=0; i<3; i++) {
        maxval=0.0;
        for (int j=0; j<3; j++) {
            cin>>val;
            if (val>maxval) {maxidx=j; maxval=val;}
        }
        product*=maxval;
        cout<<map[maxidx]<<' ';
    }
    printf("%.2f", (product*0.65-1)*2);
}

int main(int argc, char *argv[])
{
    fun1();
}
