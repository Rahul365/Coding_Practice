#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/844/B
int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> dp(n,vector<int>(m));
    for(int i = 0;i<n;++i)
        for(int j = 0;j<m;++j){
            cin >> dp[i][j];
        }
    long long int answer = 0;
    for(int r = 0;r < n;++r){
        int cnt0 = 0;
        for(int i  = 0 ;i<m;++i) cnt0 += dp[r][i]==0;
        answer += (1LL<<cnt0) + (1LL<<(m-cnt0)) - 2;
    }
    for(int c = 0; c < m;++c){
        int cnt0  = 0;
        for(int r = 0;r < n;++r) cnt0 += dp[r][c]==0;
        answer += (1LL<<cnt0) + (1LL<<(n-cnt0)) - 2;
    }
    //answer - common sets;
    cout << (answer - (n*m)) <<"\n";
    return 0;
}