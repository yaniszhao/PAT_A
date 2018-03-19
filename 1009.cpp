#include <iostream>
#include <algorithm>
#include <strstream>
#include <iomanip>
#include <vector>
using namespace std;
#define MAX 2001//乘法，所以要大小要扩大一倍

typedef struct poly{
    int exp;
    float coe;
    poly(int a, float b) : exp(a), coe(b) {};//方便初始化
} Poly;

void fun1()
{
    vector<Poly> v;
    float map[MAX]={0};
    int n, exp;
    float coe;
    ostrstream s;
    s<<fixed<<setprecision(1);//使小数点保持一位

    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>exp>>coe;
        v.push_back(Poly(exp, coe));
    }

    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>exp>>coe;
        for (int j=0; j<v.size(); j++)
            map[exp+v[j].exp]+=coe*v[j].coe;
    }

    n=0;
    for (int i=MAX; i>=0; i--) {//考虑时间还是只做一次循环
        if (map[i]!=0) {
            n++;
            s<<' '<<i<<' '<<map[i];
        }
    }
    cout<<n<<s.str();
}

//1、这题是A*B和之前的A+B不同，要多用空间存数据
//2、考虑时间还是只做一次循环，不过得花空间存要打印的信息
//3、当然也可以用两次循环代码简单，而且复杂度其实和一次循环是一样的
int main(int argc, char *argv[])
{
    fun1();
}
