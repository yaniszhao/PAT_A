#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

bool cmp(int a, int b) {return a《b;}

void fun1()
{
	vector<int> v;
	int n1, n2, val;
	cin>>n1;
	for (int i=0; i<n1; i++) {
		cin>>val;
		v.push_back(val);
	}
	cin>>n2;
	for (int i=0; i<n2; i++) {
		cin>>val;
		v.push_back(val);
	}
	sort(v.begin(), v.end(), cmp);
	cout<<v[n1+n2-1];
}

//这个代码虽然简单有三个用例会超时，想下可以优化吗
//排序用归并排序好一点，但是空间耗费就更大了
int main(int argc, char *argv[])
{
    fun1();
}
