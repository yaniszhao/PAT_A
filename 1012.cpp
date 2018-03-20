#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//把AVG放第一个是为了循环得到best
enum Sub {AVG,CHS,MATH,ENG};
char sub[]="ACME";

typedef struct stu {
    int sore[4];
    int rank[4];
    int best;//为了在得到rank的时候就获得最好科目
} Stu;

bool cmp(int a, int b) {return a>b;}

void fun1()
{
    vector<int> V[4];
    map<string, Stu> stu;
    int N,M;
    string name;
    int val[4];
    Stu st;

    cin>>N>>M;
    for (int i=0; i<N; i++) {//存入数据
        cin>>name>>val[1]>>val[2]>>val[3];
        val[0]=(val[1]+val[2]+val[3])/3;
        for (int sub=AVG; sub<=ENG; sub++) {
            V[sub].push_back(val[sub]);
            st.sore[sub]=val[sub];
        }
        stu[name]=st;
    }

    for (int i=AVG; i<=ENG; i++)//科目排序，要修改值所以it用的是引用
        sort(V[i].begin(), V[i].end(), cmp);

    for (auto &it : stu) {//获得学生排名
        it.second.best=AVG;
        for (int sub=AVG; sub<=ENG; sub++) {
            for (int j=0; j<V[sub].size(); j++)
                if (V[sub][j]==it.second.sore[sub]) {
                    it.second.rank[sub]=j+1;
                    break;
                }
            if (it.second.rank[sub]<it.second.rank[it.second.best])
                it.second.best=sub;//得到最好排名的科目
        }
    }

    for (int i=0; i<M; i++) {//按要求打印
        cin>>name;
        auto it=stu.find(name);
        if (it==stu.end())
            cout<<"N/A"<<endl;
        else {
            int best=it->second.best;
            //也可以不在结构体里放best在这里循环获得
            cout<<it->second.rank[best]<<' '<<sub[best]<<endl;
        }
    }
}

//1、是要得到排名最小的科目不是得到分数最大的科目的排名
//2、因为学生的标识是id所以可以不用map用数组也可以通过id直接得到位置
int main(int argc, char *argv[])
{
    fun1();
}
