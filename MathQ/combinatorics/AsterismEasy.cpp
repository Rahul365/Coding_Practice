#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d ",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
#define trace_vector(v) for(auto x : v) cerr << x <<" ";cerr<<"\n";
using namespace std;
const int maxn = 2e5+11;
const int MAXN = 1e5+5;
const int LG = 20;
const int INF = 1e9;
using ll = long long int;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;
ll *inv;
/*compute x^y*/
template<typename T>
T power(T a,T b,T mod = MOD1){
    T r = 1LL;
    while(b){
        if(b&1LL){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1LL;
    }
    return r;
}
/*compute inversions*/
void inversions()
{
    inv = new ll[maxn];
    inv[0]= 0;
    for(int i = 1;i<maxn;++i){
        inv[i] = power((ll)i,MOD1-2LL);
    }
}

/*compute gcd(a,b)*/
template<typename T>
T gcd(T a,T b){
    while(b){
        T t = b % a;
        a = b;
        b = t;
    }
    return a;
}

ll fact[MAXN * 5];
void computefact(){
    fact[0] = 1;
    for(ll i = 1;i < MAXN *5;++i){
        fact[i] = (fact[i-1] * i)%MOD2;
    }
}
ll ncr(ll n,ll r){
    if(n < r) return 0;
    ll answer = fact[n];
    answer = (answer * power<ll>(fact[r],MOD2-2LL,MOD2))%MOD2;
    answer = (answer * power<ll>(fact[n-r],MOD2-2LL,MOD2))%MOD2;
    return answer;
}

ll countMultiples(ll l, ll r,ll of){
    return (r/of) - (l-1)/of;
}

// https://codeforces.com/problemset/problem/1371/E1
int main(){
    int n,p;
    readint(n);
    readint(p);
    vector<int> answer;
    vector<ll> cnt(3000,0);
    int lim = 0;
    for(int i = 0; i< n;++i){
        int val;
        readint(val);
        ++cnt[val];
        lim = max(lim,val);
    }
    for(int i = 1;i<3000;++i) cnt[i]+=cnt[i-1];
    /*
     For Yuzu to win all the duels, he/she must have atleast x>=lim-n+1 candies.
     For all the values of x >= lim, any permutation will be valid. Since p <= n, those values will not be included in the answer
     We check for x in range [lim-n+1,lim) only. 
    */
    for(ll x = lim-n+1;x < lim;++x){
        ll sub = 0;
        ll fx = 1;//number of permutations for x such that Yuzu wins all the duels
        for(int i = x;i<x+n;++i){
            fx *= cnt[min(lim,i)] - sub;
            fx %= p;
            ++sub;
        }
        fx = max(0LL,fx);
        if(fx%p){
            answer.emplace_back((int)x);
        }
    }
    printf("%d\n",(int)answer.size());
    for(int v : answer) printf("%d ",v);
    return 0;
}