#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
using ll = long long int;
// https://codeforces.com/problemset/problem/553/A
/*Since mod is prime so we can Fermat little theorem*/
ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1) r = (r * a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> c(n);
    for(int i = 0;i<n;++i) cin >> c[i];
    ll answer = 1;
    ll total = 0;
    long long p = 1;
    for(int i = 0;i<n;++i){
        if(c[i]-1==0) {++total; continue;}
        total += c[i];//number of objects to choose from 
        //permutate c[i]-1 objects
        ll r = c[i]-1;
        ll curr = 1;
        ll N = total-1;
        ll d = 1;
        while(r){
            curr *= N;
            curr %= mod;
            d *= r;
            d %= mod;
            --N;
            --r;
        }
        curr = (curr%mod * pmod(d,mod-2))%mod;
        // cerr << curr << " " << total-1 <<" " << c[i]-1 <<" "<<d << "\n";
        answer = (answer * curr)%mod;
    }
    cout << answer <<"\n";
    return 0;
}