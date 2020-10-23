#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printdouble(x) printf("%.6f",x)
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

int divisibleByp(int l,int r,int p){
    return (r/p) - (l-1)/p;
}

int notdivisibleByp(int l,int r,int p){
    return r-l+1 - divisibleByp(l,r,p);
}
// https://codeforces.com/problemset/problem/621/C
int main(){
    int n,p;
    readint(n);
    readint(p);
    vector<pair<ll,ll>> arr(n);
    for(int i = 0;i<n;++i){
        int l,r;
        readint(l); readint(r);
        arr[i] = {notdivisibleByp(l,r,p),r-l+1};
    }
    /*
        Since p is the prime number , so it can be either present int flower count of i & (i+1)%n shark.
        Wet shark reward 1000 to both the sharks.
        let P(x) be the probability that product of flower count by x and (x + 1)%n sharks is divisible by p.
        P(x) = 1 - (Pi(not divisible by p) * Pj(not divisible p))
        answer = SUM(Pi(x)*2000) for i = 0 to i < n
    */
    double answer = 0.0;
    for(int i = 0;i<n;++i){
        int next = (i+1)%n;
        double prob = 1.0 - ((1.0*arr[i].first/arr[i].second) * (1.0 * arr[next].first/arr[next].second*1.0));
        // cerr << prob*2000 <<"\n";
        answer = answer +  (prob*2000.0);
    }
    printf("%.9f\n",answer);
    return 0;
}