#include <iostream>
#include <strstream>//ostrstream
#include <iomanip>//setprecision
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAX 1001

void fun1()
{
    float map[MAX]={0};
    int k,exp;
    float coe;
    for (int i=0; i<2; i++) {
        cin>>k;
        for (int j=0; j<k; j++) {
            cin>>exp>>coe;
            map[exp]+=coe;
        }
    }
    k=0;
    for (int i=MAX-1; i>=0; i--)
        if (map[i]!=0) k++;//要用!=不能用>因为可能小于0
    cout<<k;
    for (int i=MAX-1; i>=0; i--)
        if (map[i]!=0) printf(" %d %.1f", i, map[i]);
}

void fun2()
{//不能四舍五入有个用例不过
    float map[MAX]={0};
    int k,exp;
    float coe;
    string s, s1;
    for (int i=0; i<2; i++) {
        cin>>k;
        for (int j=0; j<k; j++) {
            cin>>exp>>coe;
            map[exp]+=coe;
        }
    }
    k=0;
    for (int i=MAX-1; i>=0; i--)
        if (map[i]!=0) {//要用!=不能用>因为可能小于0
            k++;
            s.append(" ").append(to_string(i)).append(" ");
            s1=to_string(map[i]);
            //s+=s1.substr(0, s1.size()-5);
            s+=s1.substr(0, s1.find('.')+2);
        }
    cout<<k<<s;
}

void fun3()
{
    float map[MAX]={0};
    int k,exp;
    float coe;
    ostrstream s;
    for (int i=0; i<2; i++) {
        cin>>k;
        for (int j=0; j<k; j++) {
            cin>>exp>>coe;
            map[exp]+=coe;
        }
    }
    k=0;
    for (int i=MAX-1; i>=0; i--)
        if (map[i]!=0) {//要用!=不能用>因为可能小于0
            k++;
            s<<fixed<<setprecision(1);
            s<<' '<<i<<' '<<map[i];
        }
    cout<<k<<s.str();
}

//fun1用两次循环，避免使用多的空间
//fun2为了一次循环，多string来存打印信息,不能四舍五入有个用例不过
//fun3为了一次循环，多strstream来存打印信息
int main(int argc, char *argv[])
{
    fun3();
}
