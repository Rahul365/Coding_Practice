#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 1e9+7;
// https://codeforces.com/problemset/problem/1105/C
int main(){
    int n,l,r;
    cin >> n >> l >> r;
    ll answer = 0;
    /**
     * Goal is to count the number of ways to fill array of n elements such that there sum is divisible by 3
     */
    /***
     * l = 13
     * r = 23
     * remainder = 0, (r/3) - (l-1)/3 => 7 - 4 = 3 number divisble by 3 in range l to r
     */
    ll c0 = (r/3) - (l-1)/3;
    ll c1 = 0;
    ll c2 = 0;
    ll ok = r-l+1;
    while(l%3 && l<=r){
        if(l%3==1) ++c1;
        else ++c2;
        ++l;
    }
    while(l<=r && r%3){
        if(r%3==1) ++c1;
        else ++c2;
        --r;
    }
    ll eq = (l<=r?(r-l)/3:0); //number of cycles formed 
    c1 += eq;//number of elements with remainder 1
    c2 += eq;//number of elements with remainder 2
    // cerr << ok << " " << c0 << " " << c1 << " " << c2<<"\n";
    assert(ok == c0 + c1 + c2);
    ll cnt[3] = {c0,c1,c2};
    ll dp[n][3];
    memset(dp,0LL,sizeof dp);
    dp[0][0] = c0;
    dp[0][1] = c1;
    dp[0][2] = c2;
    for(int pos = 1;pos < n;++pos){
        dp[pos][0] = (dp[pos-1][0]*cnt[0])%mod + (dp[pos-1][1]*cnt[2])%mod + (dp[pos-1][2]*cnt[1])%mod;
        dp[pos][0]%=mod;
        dp[pos][1] = (dp[pos-1][0]*cnt[1])%mod + (dp[pos-1][2]*cnt[2])%mod + (dp[pos-1][1]*cnt[0])%mod;
        dp[pos][1]%=mod;
        dp[pos][2] = (dp[pos-1][0]*cnt[2])%mod + (dp[pos-1][1]*cnt[1])%mod + (dp[pos-1][2]*cnt[0])%mod;
        dp[pos][2]%=mod;
    }
    cout << dp[n-1][0] <<"\n";
    return 0;
}