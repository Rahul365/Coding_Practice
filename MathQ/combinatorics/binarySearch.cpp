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

ll fact[MAXN];
void computefact(){
    fact[0] = 1;
    for(ll i = 1;i < MAXN;++i){
        fact[i] = (fact[i-1] * i)%MOD1;
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
vector<vector<ll>> nCr(2002,vector<ll>(2002));
void computeCombinations(){
    nCr[0][0] = 1;//nCr(0,0)
    for(int n = 1;n<=1000;++n){
        nCr[n][0] = nCr[n][n] = 1;
        for(int r = 1;r < n;++r){
            nCr[n][r] = (nCr[n-1][r] + nCr[n-1][r-1]);
            if(nCr[n][r]>=MOD1){
                nCr[n][r]-=MOD1;
            }
            else if(nCr[n][r]<0){
                nCr[n][r]+=MOD1;
            }
        }
    }
}

// https://codeforces.com/problemset/problem/1436/C
ll getanswer(int n,int x,int pos){
    ll l = 0;
    ll r = n;
    ll cntlt = x-1;//number of elements < x
    ll cntgt = n-x;//number of elements > x
    ll answer = 1;
    ll m;
    while(l<r){
        m = (l+r)/2;
        if(m<=pos){
            if(m<pos){
            answer = (answer * cntlt)%MOD1;
            --cntlt;
            }
            l = m+1;
        }
        else{
            answer = (answer * cntgt)%MOD1;
            --cntgt;
            r = m;
        }
    }
    // cerr << l << " " << pos <<"\n";
    // answer = (fact[x-1] * power<ll>(fact[cntlt],MOD1-2))%MOD1;
    // answer = (answer * (fact[n-x] * power<ll>(fact[cntgt],MOD1-2))%MOD1)%MOD1;
    if(cntlt<0 || cntgt<0) answer = 0;
    answer = (answer * fact[cntlt+cntgt])%MOD1;
    return answer;
}

int main(){
    computefact();
    // computeCombinations();
    int n,x,pos;
    readint(n); readint(x); readint(pos);
    printint64(getanswer(n,x,pos));
    return 0;
}