#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9+7;
// https://codeforces.com/problemset/problem/1288/C
ll gcd(ll a,ll b){
    while(b){
        ll t = a%b;
        a = b;
        b = t;
    }
    return a;
}

ll ncr(ll n,ll r){
    r = min(r,n-r);
    ll p = 1,k = 1;
    while(r){
        p *= n;
        k *= r;
        ll d = gcd(p,k);
        p /= d;
        k /= d;
        p %= mod;
        --n;
        --r;
    }
    return p;
}

/***
 * Not before reading the editorial I realize it.
 * We can just view the whole problem as sequence of length 2m
 * a1,a2,a3,...,am,bm,bm-1,bm-2,...b1
 * Now we can just count the combinations to fill this sequence with repetitions using 1 to n elements
 * which is C(n+2*m-1,2*m)
 * */
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    ll answer =  ncr(n+2*m-1,2*m)%mod;
    printf("%lld\n",answer);
    return 0;
}