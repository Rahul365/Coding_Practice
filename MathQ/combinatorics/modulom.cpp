#include<bits/stdc++.h>
using namespace std;
//PigeonHole principle + DP + Observations + Difficulty Level 1900
// https://codeforces.com/problemset/problem/577/B
void max_self(int &a,int b){
    a = max(a,b);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; long long int m; cin >> n >> m;
    vector<long long int> a(n);
    vector<long long int> fq(m+1);
    for(int i = 0;i<n;++i){
        cin >> a[i];
        a[i]%=m;
        ++fq[a[i]];
    }
    //consider two cases
    if(n >= m){
        //there always exists such combination by pigeon hole principle such that whose sum is divisible by m
        cout << "YES\n";
    }
    else{
        bool ok = fq[0];
        //use DP
        vector<vector<int>> dp(n+1,vector<int>(m+1,-1));//dp[index][r]=> we acheive r = sum%m with index-1 elements
        //dp[index+1][(r+a[index])%m] || dp[index+1][r]
        for(int i = 0;i<=n;++i){
            for(int j = 0;j<=m;++j){
                dp[i][j] = -1;
            }
        }
        /*
        function<bool(int,int)> rec = [&](int n,int sum){
            if(sum>0 && sum%m == 0) return true;
            if(n == 0) return false;
            int &ans = dp[n][sum%m];
            if(ans!=-1) return ans == 1;
            ans = 0;
            return (ans = rec(n-1,sum + a[n-1]) || rec(n-1,sum))==1;
        };
        */
        dp[0][a[0]] = 1;
        for(int pos = 1;pos < n;++pos){
            dp[pos][a[pos]] = 1;
            for(int sum = 0;sum<=m;++sum){
                if(sum + a[pos])
                max_self(dp[pos][(sum+a[pos])%m],dp[pos-1][sum]);
                max_self(dp[pos][sum],dp[pos-1][sum]);
            }
        }
        cout << (ok || /*rec(n,0)*/dp[n-1][0]==1 ? "YES":"NO") <<"\n";
    }
    return 0;
}