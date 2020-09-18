#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9+7;
// https://codeforces.com/problemset/problem/677/C
int main(){
    vector<int> chv(256,-1);
    chv['0'] = 0;
    for(char ch = '1' ; ch <= '9';++ch)
        chv[ch] = 1 + chv[ch-1];
    chv['-'] = 62;
    chv['_'] = 63;
    chv['A'] = 10;
    for(char ch = 'B' ; ch <= 'Z';++ch){
        chv[ch] = 1 + chv[ch-1];
    }
    chv['a'] = 36;
    for(char ch = 'b';ch <= 'z' ;++ch)
    {
        chv[ch] = 1 + chv[ch-1];
    }
    //count the number of pairs of Strings(A,B) of length |S| such
    //that biwise and of their base 64 representation = A & B = S  
    vector<long long int> dp(64,0);
    for(int i = 0;i<64;++i)
        for(int j = 0;j<64;++j) 
        {
            dp[i&j]++;//Number of pairs of the base64 values designed in the question that give result => i&j
        }
    string s;
    cin >> s;
    long long answer = 1;//There is always 1 answer possible S & S = S
    //answer = Number of ways to Choose pair of Strings =  (# of Pairs for s[0]) * (# of pairs for s[1]) * (# of pairs for s[2])*....*(# of pairs for s[n-1])
    for(char ch : s){
        assert(chv[ch]!=-1);
        answer = (answer * dp[chv[ch]])%mod;
    }
    cout << answer <<"\n";
    return 0;
}