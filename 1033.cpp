#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
    float price;
    int dis;
} Sta;

vector<Sta> sta;

bool cmp(Sta a, Sta b)
{
    return a.dis<b.dis;
}

int NextCheaperIndex(int u, int maxdis)
{//比当前更便宜且能到达的站点
    for (int i=u+1; i<sta.size(); i++)
        if (sta[i].dis>maxdis) return -1;//超出距离
        else if (sta[i].price<sta[u].price) return i;
    return -1;//没有更便宜的，或者是最后一个
}

int NextProperIndex(int u, int maxdis)
{//能到达得相对最便宜的站点
    int min=u+1;
    if (u==sta.size()-1) return -1;
    if (sta[min].dis>maxdis) return -1;
    for (int i=min+1; i<sta.size(); i++)
        if (sta[i].dis>maxdis) break;
        else if (sta[i].price<sta[min].price) min=i;
    return min;
}

void fun1()
{
    int cap,dis,avg,n;
    int i,cur=0,surp=0,next;
    float sum=0;
    Sta tmp;

    cin>>cap>>dis>>avg>>n;
    cap=cap*avg;
    for (i=0; i<n; i++) {
        cin>>tmp.price>>tmp.dis;
        tmp.price/=avg;//换成每米的价格
        sta.push_back(tmp);
    }

    sort(sta.begin(), sta.end(), cmp);
    if (sta[0].dis!=0) {
        printf("The maximum travel distance = %.2f", (float)cur);
        return;
    }

    for (i=0; i<sta.size() && cur<dis;) {
        //最后一个站点
        if (i==sta.size()-1) {
            if (cur+cap<dis) {//无法到达终点，加满走到最远
                sum+=sta[i].price*(cap-surp);
                cur+=cap;
                break;
            }
            else {//可以走到终点,在输入做了处理就可以不要这个判断
                sum+=sta[i].price*(dis-cur-surp);
                cur=dis;
                break;
            }
        }
        //不是最后一个
        next=NextCheaperIndex(i, cur+cap);
        if (next>-1) {//有更便宜的且能到达的站点
            if (sta[next].dis<dis) {//站点小于终点，去站点
                sum+=sta[i].price*(sta[next].dis-cur-surp);
                surp=0;
                cur=sta[next].dis;
                i=next;
            }
            else {//站点大于终点，去终点
                sum+=sta[i].price*(dis-cur-surp);
                cur=dis;
                break;
            }
        }
        else {//没有更便宜的站点
            if (cur+cap>=dis) {//能走到终点，加到终点的油
                sum+=sta[i].price*(dis-cur-surp);
                cur=dis;
                break;
            }
            else {//不能走到终点，走到相对最便宜的，但是油加满
                next=NextProperIndex(i, cur+cap);
                if (next==-1) {//下一个站点太远，走不到,加满走到最远
                    sum+=sta[i].price*(cap-surp);
                    cur+=cap;
                    break;
                }
                else {//走到下一个相对便宜的站点
                    sum+=sta[i].price*(cap-surp);
                    surp=cap+cur-sta[next].dis;
                    cur=sta[next].dis;
                    i=next;
                }
            }
        }
    }

    if (cur==dis) printf("%.2f", sum);
    else printf("The maximum travel distance = %.2f", (float)cur);
}

void fun2()
{//本来打算减少些代码的，但这个函数不可行
    int cap,dis,avg,n;
    int i,cur=0,surp=0,next;
    float sum=0;
    Sta tmp;

    cin>>cap>>dis>>avg>>n;
    cap=cap*avg;
    for (i=0; i<n; i++) {
        cin>>tmp.price>>tmp.dis;
        tmp.price/=avg;//换成每米的价格
        sta.push_back(tmp);
    }

    sort(sta.begin(), sta.end(), cmp);
    if (sta[0].dis!=0) {
        printf("The maximum travel distance = %.2f", (float)cur);
        return;
    }

    for (i=0; i<sta.size() && cur<dis;) {
        //最后一个站点
        if (i==sta.size()-1) {
            if (cur+cap<dis) {//无法到达终点，加满走到最远
                sum+=sta[i].price*(cap-surp);
                cur+=cap;
                break;
            }
            else {//可以走到终点
                sum+=sta[i].price*(dis-cur-surp);
                cur=dis;
                break;
            }
        }
        //不是最后一个站点，且能走到终点
        //fun2错在这里，因为在终点前可能有更便宜的站点
        if (cur+cap>=dis) {//能走到终点，加到终点的油
            sum+=sta[i].price*(dis-cur-surp);
            cur=dis;
            break;
        }
        //不是最后一个站点，且不能走到终点
        next=NextCheaperIndex(i, cur+cap);
        if (next==-1) {//没有更便宜的站点
            next=NextProperIndex(i, cur+cap);
            if (next==-1) {//下一个站点太远，走不到,加满走到最远
                sum+=sta[i].price*(cap-surp);
                cur+=cap;
                break;
            }
            else {//走到下一个相对便宜的站点
                sum+=sta[i].price*(cap-surp);
                surp=cap+cur-sta[next].dis;
                cur=sta[next].dis;
                i=next;
            }
        }
        else {//有更便宜的且能到达的站点，且肯定在终点前面
            sum+=sta[i].price*(sta[next].dis-cur-surp);
            surp=0;
            cur=sta[next].dis;
            i=next;
        }
    }

    if (cur==dis) printf("%.2f", sum);
    else printf("The maximum travel distance = %.2f", (float)cur);
}

void fun3()
{//减少了是否是最后一个站点的判断和避免更便宜的站点在终点之后
    int cap,dis,avg,n;
    int i,cur=0,surp=0,next;
    float sum=0;
    Sta tmp;

    cin>>cap>>dis>>avg>>n;
    cap=cap*avg;
    for (i=0; i<n; i++) {
        cin>>tmp.price>>tmp.dis;
        if (tmp.dis>=dis) continue;//避免更便宜的站点在终点之后
        tmp.price/=avg;//换成每米的价格
        sta.push_back(tmp);
    }

    sort(sta.begin(), sta.end(), cmp);
    if (sta[0].dis!=0) {
        printf("The maximum travel distance = %.2f", (float)cur);
        return;
    }

    for (i=0; i<sta.size() && cur<dis;) {
        next=NextCheaperIndex(i, cur+cap);
        if (next>-1) {//有更便宜的且能到达的站点
            sum+=sta[i].price*(sta[next].dis-cur-surp);
            surp=0;
            cur=sta[next].dis;
            i=next;
        }
        else {//没有更便宜的站点，或者i是最后一个站点
            if (cur+cap>=dis) {//能走到终点，加到终点的油
                sum+=sta[i].price*(dis-cur-surp);
                cur=dis;
                break;
            }
            else {//不能走到终点，走到相对最便宜的，但是油加满
                next=NextProperIndex(i, cur+cap);
                if (next==-1) {//下一个站点太远走不到,或者i是最后一个站点，加满走到最远
                    sum+=sta[i].price*(cap-surp);
                    cur+=cap;
                    break;
                }
                else {//走到下一个相对便宜的站点
                    sum+=sta[i].price*(cap-surp);
                    surp=cap+cur-sta[next].dis;
                    cur=sta[next].dis;
                    i=next;
                }
            }
        }
    }

    if (cur==dis) printf("%.2f", sum);
    else printf("The maximum travel distance = %.2f", (float)cur);
}

/*
 每个站点判断一次：
 1、能找到比当前站点更便宜的站点：
     1）在终点前，加恰好到那个站的油
     2）在终点后，去终点
 2、不能找到更便宜的：
     1）当前是最便宜的，能到终点去终点
     2）不能去终点去后面最便宜的站点：
 3、后面没有站点或者站点太远，加满开到最远
 */
//1、后面没有更便宜时加满走到相对便宜的，不是走到最远能到的站点
//2、用float也能过，但是涉及钱的最好还是用double
//3、即使某一个站点能立即到终点不能直接去，因为可能中间有更便宜的站点，fun2不可行
int main(int argc, char *argv[])
{
    fun3();
}
