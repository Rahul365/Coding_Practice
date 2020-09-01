#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll  mod = 998244353;
// https://codeforces.com/problemset/problem/1195/D1
void addself(ll &a,ll b){
    a = (a%mod + b%mod)%mod;
    if(a < 0) a+=mod;
}

ll getsum(string x,ll n){
    ll f1 = 0;
    ll f2 = x.back()-'0';
    ll p  = 10;
    ll p1 = 100;
    ll sum = 0;
    for(int i = x.length()-1;i>=0;--i){
        f1 = ((ll)(x[i]-'0')%mod * p%mod)%mod;
        addself(sum,(n%mod*f1%mod)%mod);
        p  = (p*100)%mod;
    }
    addself(sum,(n*f2)%mod);
    for(int i = x.length()-2;i>=0;--i){
        f2 = ((ll)(x[i]-'0')%mod * p1%mod)%mod;
        addself(sum,(n%mod*f2%mod)%mod);
        p1 = (p1 * 100)%mod;
    }
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll answer = 0;
    for(int i= 0;i<n;++i){
        string x;
        cin >> x;
        addself(answer,(getsum(x,n))%mod);
    }
    cout << answer <<"\n";
    return 0;
}