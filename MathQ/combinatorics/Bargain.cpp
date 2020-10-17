#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/1422/C
const ll mod = 1e9+7;
ll count(ll n){
    return (n*(n+1))/2;
}

void addself(ll &A,ll B){
    A = ((A + B)%mod + mod)%mod;
}

ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1;
    }
    return r;
}

int main(){
    string s;
    cin >> s;
    ll n = s.length();
    ll answer = 0;
    ll right_sum = 0LL;
    /*Precomputing the sum  = SUMMAND(10^(R-1) * R) where 1<=R<n*/
    for(ll i = n-1;i>=1;--i){
        addself(right_sum, pmod(10LL,i-1)%mod * i%mod);
    }
    for(ll i = 1;i<=n;++i){
        ll num = s[i-1] - '0';
        /*Assume that we are removing consecutive set of digits from left side only,
         so we'll be adding current digit num to answer that number of times exactly*/
        ll left = (count(i-1)%mod * num%mod * pmod(10LL,n-i)%mod)%mod;
        /*
        ll onright = n-i;
        ll right = 0LL;
        while(onright>0LL){
            right = (right + (1LL * num * pmod(10LL,onright-1LL) * onright)%mod) %mod;
            --onright;
        }
        */
        // cerr << left << " " << right <<"\n";
        addself(answer,left);
        addself(answer,num%mod * right_sum%mod);
        if(n-i)
        addself(right_sum,-1LL * pmod(10LL,n-i-1)%mod*(n-i)%mod);
    }
    cout << answer <<"\n";
    return 0;
}