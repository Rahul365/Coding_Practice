#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1238/D
int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    long long int answer = n;
    answer = (answer * (answer + 1))>>1;
    long long int cntbad = 0;//number of bad substrings
    /*
    answer = Total number of substrings - number of bad substrings
    There are only four types of strings which are not good:
    1) AAAA...AB
    2) BAA...AAA
    3) BBBB...BA
    4) ABB..BBB
    */
    char prev = s[0];
    int cnt = 1;
    cntbad += n;//all substrings of length 1 are bad
    vector<pair<char,int>> data;
    for(char ch : s){
        if(data.size() == 0 || data.back().first!=ch)
            data.emplace_back(ch,1);
        else
            data.back().second++;
    }
    for(int i = 1;i < data.size();++i){
       cntbad += data[i].second + data[i-1].second - 1;
       //-1 is for intersection part
       //e.g. AAA(AB)BBB
    }
    // cerr << answer << " " << cntbad <<"\n";
    cout << (answer - cntbad) <<"\n";
    return 0;
}