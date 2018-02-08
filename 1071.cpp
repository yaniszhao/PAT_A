#include <iostream>
#include <map>
#include <cctype>
#include <string>
using namespace std;

map<string, int> words;
map<string, int>::iterator it;
string s;
string word;

void GetWord()
{
    static int i=0;
    word.clear();
    for (; i<s.size()&&!isalnum(s[i]); i++);
    if (i==s.size()) return;
    for (; isalnum(s[i]); i++)
        word+=s[i];
}

void fun1()
{
    int i,max=-1;
    getline(cin, s);
    GetWord();
    while (word.size()!=0) {
        for (i=0; i<word.size(); i++)//大写变小写
            if (word[i]<97&&word[i]>=65)//不要变数字
                word[i]=word[i]+32;
        it=words.find(word);
        if (it!=words.end()) words[word]++;
        else words[word]=1;

        GetWord();
    }

    for (it=words.begin(); it!=words.end(); it++)
        if (it->second>max) {word=it->first; max=it->second;}
    cout<<word<<' '<<max;
}

int main(int argc, char *argv[])
{
    fun1();
}


