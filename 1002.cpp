#include <iostream>
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
            s+=s1.substr(0, s1.size()-5);
        }
    cout<<k<<s;
}

void fun2()
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

//fun1为了一次循环，多用了空间来存打印信息
//fun2用两次循环，避免使用多的空间
int main(int argc, char *argv[])
{
    fun1();
}
