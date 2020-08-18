#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
// https://codeforces.com/problemset/problem/804/B
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    long long int answer = 0;
    const int n = s.length();
    long long int cntb = 0;
    for(int i = n-1;i>=0;--i){
        if(s[i] == 'b') ++cntb;
        else{
            (answer += cntb)%=mod;
            (cntb *= 2)%=mod;
        } 
    }
    cout << answer <<"\n";
    return 0;
}