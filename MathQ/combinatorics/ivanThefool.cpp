#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9+7;
const int maxn = 1e5+1;
ll fact[maxn];
ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a*a)%mod;
        b >>= 1;
    }
    return r;
}
// https://codeforces.com/problemset/problem/1239/A

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fact[0] = 1;
    for(ll i = 1;i<maxn;++i){
        fact[i] = (i * fact[i-1])%mod;
    }
    auto countwisely=[&](ll n){
        ll ans = 0;
        /*
        using number of ways to place 'blk' blocks of size 2 in Bins
        */
        for(int blk = 1;blk <=(n>>1);++blk){
            ll bins = n - (2 * blk) + 1;
            ll obj = blk;
            ll sub = (fact[bins+obj-1]*pmod(fact[obj],mod-2))%mod;
            sub = (sub * pmod(fact[bins-1],mod-2))%mod;
            ans = (ans + (2*sub)%mod)%mod;
        }
        return ans;
    };
    int n,m;
    cin >> n >> m;
    ll answer = 2;//if there are 0 neghbour with the same color
    answer = (answer + countwisely(m))%mod;
    answer = (answer + countwisely(n))%mod;
    cout << answer <<"\n";
    return 0;
}