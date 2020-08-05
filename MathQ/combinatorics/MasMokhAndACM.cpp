#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
// https://codeforces.com/problemset/problem/414/B
int main(){
    int n,k;
    cin >> n >> k;
    vector<int> dp[n+1];
    for(int i = n;i>=1;--i){
        for(int j = i;j<=n;++j){
            if(j%i==0) dp[i].push_back(j);
        }
    }
    // for(int i= 1;i<=n;++i)   for(int j = 0;j<dp[i].size();j++)    cerr << dp[i][j] <<" \n"[j==dp[i].size()-1];

    vector<vector<int>> used(k+1,vector<int>(n+1,0));

    for(int i = 1;i<=n;++i) used[k][i] = 1;
    //dp[curr]=>holds the number of those elements 
    //used[pos][curr] => contains the number of sequence of length (k-pos) so far such 
    //curr divides next={dp[curr]}
    for(int pos = k-1;pos;--pos)
        for(int curr= 1;curr<=n;++curr)
                for(int &next : dp[curr]){
                        used[pos][curr]+=used[pos+1][next];
                        if(used[pos][curr] >= mod)
                        used[pos][curr] -=mod;
                }

    // for(int pos = 1;pos <=k ;++pos){
    //     for(int i= 1;i<=n;++i) cout << used[pos][i] <<" \n"[i==n];
    // }
    int ans = 0;
    for(int i = 1;i<=n;++i){
        ans += used[1][i];
        if(ans >= mod){
            ans -= mod;
        }
    }
    cout << ans <<"\n";
    return 0;
}