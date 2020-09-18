#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 998244353;
const int maxn = 1e6+1;
// https://codeforces.com/problemset/problem/1091/D
ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1) r = (r * a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return r;
}

int main(){
    ll n;
    scanf("%lld",&n);
    /*
    There are two types of subarrays we are looking at here : 
    1) They are fully  formed subarray of length n
    2) They are formed by suffix of length k from current permutation and prefix of length n-k from next permutation
    There are n! subarrays of the first type.
    Answer = n*n! - sum(n!/k!) where k = 1 to n-1
    */
    ll fn = n;
    for(ll i = 1;i<=n;++i) fn = (fn * i)%mod;
    ll answer = fn;
    ll fk = n;
    ll sum = 0;
    for(ll k = n-1;k>=1;--k){
        answer = answer - fk;
        if(answer <= 0) answer += mod;
        fk = (fk * k)%mod;
    }
    printf("%lld\n",answer);
    return 0;
}
