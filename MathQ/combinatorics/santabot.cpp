#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
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
    inv = new ll[MAXN*10];
    inv[0]= 0;
    for(int i = 1;i<MAXN*10;++i){
        inv[i] = power((ll)i,MOD2-2LL,MOD2);
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

template<typename T>
void multiply(T &a,T b){
    a = (1LL * a * b)%MOD2;
}

template<typename T>
void addself(T&a,T b){
    a = (a + b);
    if(a >= MOD2) a-=MOD2;
    else if(a < 0) a+=MOD2;
}
int freq[MAXN*10];

int main(){
    // https://codeforces.com/problemset/problem/1279/D
    inversions();
    memset(freq,0,sizeof freq);
    int n;
    readint(n);
    vector<int> a[n];//kids
    for(int i = 0;i<n;++i)
    {
        int k;
        readint(k);
        for(int j=0;j<k;++j){
            a[i].emplace_back();
            readint(a[i].back());
            ++freq[a[i].back()];
        }
    }
    /*
        Probability of selecting a kid x out of n kids  = 1/n
        Probability of selecting a gift out K gifts of kid(x) = 1/K
        Thus , Probability of selecting pair x and y = (1/n) and (1/K)
        Now probability of selecting a kid z out of n kids  = 1/n
        Number of kids who likes the gift y = CountOfkidsLikeYToy(y);
        Probability that kid z likes the toy y  = #of kids who likes toy y/ total # of kids = frq(y)/n
        So probability of making a right decision = P(x,y) * P(z such that z kid likes y item) = (1/n)*(1/K)*(frq(y)/n); 
    */
    ll answer = 0;
    for(int i= 0;i<n;++i){
        for(int y : a[i]){
            ll prob = inv[n];
            multiply(prob,inv[(int)a[i].size()]);
            multiply(prob,(ll)freq[y]);
            multiply(prob,inv[n]);
            addself(answer,prob);
        }
    }
    printint64(answer);
    return 0;
}