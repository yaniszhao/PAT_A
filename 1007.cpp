#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void fun1()
{//brute force
    vector<int> v;
    int k,flag=0;
    int i,j,sum=-1;
    cin>>k;
    v.resize(k);
    for (i=0; i<k; i++) {
        cin>>v[i];
        if (v[i]>=0) flag=1;//注意0要包含进去
    }

    //全负数，sum为0，而且也要打印第一个和最后一个数
    if (flag==0) {cout<<0<<' '<<v.front()<<' '<<v.back(); return;}

    for (int a=0; a<v.size(); a++) {
        int tsum=0;
        if (v[a]<0) continue;
        //进入循环证明至少有一个数>=0
        for (int b=a; b<v.size(); b++) {
            tsum+=v[b];
            if (tsum>sum) {sum=tsum; i=a; j=b;}
        }
    }
    //cout<<sum<<' '<<i<<' '<<j;//打印值，不是下标
    cout<<sum<<' '<<v[i]<<' '<<v[j];
}

//参考liuchuo的代码，类似leetcode上速度最快的那种方法。
void fun2()
{
    vector<int> v;
    int k,flag=0;
    int i,j,sum=-1;
    int tsum=0, nexti=0;
    cin>>k;
    v.resize(k);
    for (i=0; i<k; i++) {
        cin>>v[i];
        if (v[i]>=0) flag=1;//注意0要包含进去
    }

    //全负数，sum为0，而且也要打印第一个和最后一个数
    if (flag==0) {cout<<0<<' '<<v.front()<<' '<<v.back(); return;}

    for (int k=0; k<v.size(); k++) {//能走到这证明至少有一个数>=0
        tsum+=v[k];
        //当已经一段序列和大于0时，要么后面越加越大，要么就是中间有一段负数太大导致和变成负数，
        //那么能组成比前一段更大序列和的起始点肯定是下一个正数
        if (tsum<0) {
            tsum=0;
            nexti=k+1;
        }
        else if (tsum>sum) {
            sum=tsum;
            i=nexti; j=k;
        }
    }
    cout<<sum<<' '<<v[i]<<' '<<v[j];
}

//fun1是暴力破解，复杂度O(n^2)，这题时间还可以接受
//fun2是改进后的算法，复杂度只有O(n)，但不容易理解
//求最大子串一般4种方法：暴力法、分治法、分析法、动态规划
//详细的多种解法参见leetcode的53题
int main(int argc, char *argv[])
{
    fun2();
}
