#include<bits/stdc++.h>
using namespace std;
using ll = long long int ;
// https://codeforces.com/problemset/problem/608/B
int main(){
    string s,p;
    cin >> s >> p;
    int n = s.length();
    int m = p.length();
    vector<vector<int>> dp(m+1,vector<int>(2,0));
    for(int i = 1;i<=m;++i){
        dp[i][p[i-1]-'0'] = 1;
        for(int j = 0;j<2;++j) dp[i][j] += dp[i-1][j];
    }
    long long int answer = 0;
    for(int i = 0;i<n;++i){
        for(char ch  : {'0','1'}){
            //(s[i] & ch are not the same) * (count of ch in the positions which will be matching with s[i] in p[])
            answer += abs(s[i]-ch) * (dp[m-n+i+1][ch-'0'] - dp[i][ch-'0']);//how many positions are occupied by current s[i] in p[]
        }
    }
    cout << answer <<"\n";
    return 0;
}