#include<bits/stdc++.h>
#define speedup ios_base::sync_with_stdio(false); cin.tie(0)
using namespace std;
const int mod = 1e9+7;
using ll = long long int;
template<typename T>
T power(T x,T y){
    T r = 1;
    while(y){
        if(y&1){
            r = (r * x)%mod;
        }
        x = (x * x)%mod;
        y >>= 1;
    }
    return r;
}
const int maxn = 1e5+1;
vector<pair<ll,ll>> steps(maxn);
int main(){
    steps[0] = {1,1};//{extra,removed}
    for(int i = 1;i<maxn;++i){
        steps[i] = {steps[i-1].first + (steps[i-1].first * steps[i-1].second),steps[i-1].second+2};
    }
    speedup;
    // int sum = (2 + power(4LL,3LL) + power(256LL,5LL));cout << sum <<"\n";
    int t;
    cin >> t;
    while(t--){
        ll n,q;
        cin >> n >> q;
        ll ans = 0;
        ll product = q;
        for(int i = 0;i<n;++i){
            ll extra = steps[i].first;
            ll removed = steps[i].second;
            //  cout << extra <<" "<<removed <<"\n";
            // ll product = power(power(q,extra),removed);
            ll prev = product;
            product = power(product,removed);
            ans += product;
            product *= prev;
            if(product >= mod) product %= mod;
            if(ans >= mod) ans-=mod;
        }
        cout << ans <<"\n";
    }
    return 0;
}