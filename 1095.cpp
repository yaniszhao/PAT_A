#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
    string plate;
    int tm;
    int status;//0-in,1-out
} Car;

int TimeToInt(string time)
{
    int hour, mins, sec;
    hour=(time[0]-'0')*10+time[1]-'0';
    mins=(time[3]-'0')*10+time[4]-'0';
    sec=(time[6]-'0')*10+time[7]-'0';
    return hour*3600+mins*60+sec;
}

char* IntToTime(int tm)
{
    static char time[9];
    int h,m,s;
    h=tm/3600; tm%=3600;
    m=tm/60; tm%=60;
    s=tm;
    sprintf(time, "%02d:%02d:%02d", h, m, s);
    time[8]=0;
    return time;
}

bool cmp1(Car a, Car b)
{
    if (a.plate==b.plate)
        return a.tm<b.tm;
    return a.plate<b.plate;
}

bool cmp2(Car a, Car b)
{
    return a.tm<b.tm;
}

void fun1()
{
    map<string, int> map;
    vector<int> total;
    vector<Car> car;
    vector<int> query;
    Car tmpcar;
    string plate, time, status;
    int n,k;
    int i,j,cnt=0,max=-1;
    //处理输入
    cin>>n>>k;
    for (i=0; i<n; i++) {
        cin>>plate>>time>>status;
        if (map.find(plate)==map.end()) map[plate]=map.size();
        tmpcar.plate=plate;
        tmpcar.tm=TimeToInt(time);
        tmpcar.status=status=="in"?0:1;
        car.push_back(tmpcar);
    }
    for (i=0; i<k; i++) {
        cin>>time;
        query.push_back(TimeToInt(time));
    }
    //可能有连续几次进入或者出去的，要排序处理
    sort(car.begin(), car.end(), cmp1);
    for (i=n-2; i>=0; i--) {//erase会改变大小，所以从后往前删
        if (car[i].plate==car[i+1].plate&&car[i].status==car[i+1].status) {
            if (car[i].status==0) car.erase(car.begin()+i);//in
            else car.erase(car.begin()+i+1);//out
        }
    }
    //顺便用这次的排序把总停留时间和最大停留时间求出来
    plate=car[0].plate;
    total.assign(map.size(), 0);
    for (i=1; i<car.size(); i++) {
        if (car[i].plate==plate) {
            if (car[i].status==1)//out
                total[map[plate]]+=car[i].tm-car[i-1].tm;
        }
        else plate=car[i].plate;
    }
    for (i=0; i<total.size(); i++)
        if (total[i]>max) max=total[i];
    //处理完无效数据再从新按时间排序
    sort(car.begin(), car.end(), cmp2);
    for (i=0,j=0; i<k&&j<car.size();) {
        if (car[j].tm<=query[i]) {
            if (car[j].status==0) cnt++;//in
            else  cnt--;//out
            j++;
        }
        else {
            cout<<cnt<<endl;
            i++;
        }
    }
    //if (j==car.size()&&car[j-1].tm<=query[i]) cout<<cnt<<endl;
    for (; i<k; i++) cout<<cnt<<endl;//记录完了，但查询还没完，光用if不行
    //打印停留最多时间
    for (auto it:map)
        if (total[it.second]==max) cout<<it.first<<" ";
    cout<<IntToTime(max);
    //printf("%s",IntToTime(max));
}

void fun2()
{
    map<string, int> total;//直接用map了不用map加vector
    vector<Car> rec, car;//多用一个vector记录数据，另外一处存有效数据
    vector<int> query;
    Car tmpcar;
    string plate, time, status;
    int n,k;
    int i,j,cnt=0,max=-1;
    //处理输入
    cin>>n>>k;
    for (i=0; i<n; i++) {
        cin>>plate>>time>>status;
        tmpcar.plate=plate;
        tmpcar.tm=TimeToInt(time);
        tmpcar.status=status=="in"?0:1;
        rec.push_back(tmpcar);
    }
    for (i=0; i<k; i++) {
        cin>>time;
        query.push_back(TimeToInt(time));
    }
    //可能有连续几次进入或者出去的，要排序处理
    sort(rec.begin(), rec.end(), cmp1);
    for (i=0; i<n-1; i++) {//正向读取有效信息
        if (rec[i].plate==rec[i+1].plate&&rec[i].status==0&&rec[i+1].status==1) {
            car.push_back(rec[i]);
            car.push_back(rec[i+1]);
        }
    }
    //顺便用这次的排序把总停留时间和最大停留时间求出来
    plate=car[0].plate;
    total[plate]=0;
    for (i=1; i<car.size(); i++) {
        if (car[i].plate==plate) {
            if (car[i].status==1) {//out
                total[plate]+=car[i].tm-car[i-1].tm;
                if (total[plate]>max) max=total[plate];
            }
        }
        else {
            plate=car[i].plate;
            total[plate]=0;
        }
    }
    //处理完无效数据再从新按时间排序
    sort(car.begin(), car.end(), cmp2);
    for (i=0,j=0; i<k&&j<car.size();) {//这里的处理方式也很有意思
        if (car[j].tm<=query[i]) {
            if (car[j].status==0) cnt++;//in
            else  cnt--;//out
            j++;
        }
        else {
            cout<<cnt<<endl;
            i++;
        }
    }
    for (; i<k; i++) cout<<cnt<<endl;//记录完了，但查询还没完，光用if不行
    //打印停留最多时间
    for (auto it:total)
        if (it.second==max) cout<<it.first<<" ";
    cout<<IntToTime(max);
}

//1、一开始拿到题很头疼，既要处理无效数据还要对有效数据处理，但是想到用2次排序就好做了
//2、可能连续进几次或或者出几次，要排除无效数据
//3、对数据的处理如果直接删除，可能还是有无效数据，最好还是正面取有效数据如fun2
//4、这题的处理太多用c不合适，直接上cpp了，据说用cin会超时，但是我这还没有超时
int main(int argc, char *argv[])
{
    fun2();
}
