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
const int maxn = 3e5+11;
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
/*compute inverse of numbers*/
void inverses()
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
// https://codeforces.com/problemset/problem/1207/D
ll fact[maxn];
int main(){
    fact[0] = 1;
    for(int i = 1;i<maxn;++i){
        fact[i] = (1LL * i * fact[i-1])%MOD2;
    }
    int n;
    readint(n);
    vector<pair<int,pair<int,int>>> p(n+1);
    for(int i=1;i<=n;++i){
        readint(p[i].first);
        readint(p[i].second.first);
        p[i].second.second = i;
    }
    //sort by a[]
    sort(p.begin()+1,p.end());
    if(p[1].first == p[n].first){
        printf("0");
        return 0;
    }
    ll badA = 1;
    ll common = 1;
    ll curr = -1;
    int cnt = 1;
    for(int i = 1;i<=n;++i){
        if(p[i].first!=curr){
            badA = (badA * fact[cnt])%MOD2;
            curr = p[i].first;
            cnt = 1;
        }
        else{
            ++cnt;
            if(i == n){
                badA = (badA * fact[cnt])%MOD2;
            }
        }
        if(p[i].second.first < p[i-1].second.first){
            common = 0;
        }
    }
    /*Counting number of permutations where both sequence are sorted simultaneously*/
    pair<int,int> prev = {-1,-1};
    cnt = 0;
    for(int i = 1;i<=n;++i){
        pair<int,int> now = {p[i].first,p[i].second.first};
        if(prev!=now){
            common = (common * fact[cnt])%MOD2;
            prev = now;
            cnt = 1;
        }
        else{
            ++cnt;
            if(i == n){
                common = (common * fact[cnt])%MOD2;
            }
        }
    }
    for(int i = 1;i<=n;++i){
        swap(p[i].first,p[i].second.first);
    }
    //sort by b[]
    sort(p.begin()+1,p.end());
    if(p[1].first == p[n].first){
        printf("0");
        return 0;
    }
    ll badB = 1;
    curr = -1;
    cnt = 1;
    for(int i = 1;i<=n;++i){
        if(p[i].first!=curr){
            badB = (badB * fact[cnt])%MOD2;
            curr = p[i].first;
            cnt = 1;
        }
        else{
            ++cnt;
            if(i == n){
                badB = (badB * fact[cnt])%MOD2;
            }
        }
    }
    /*
    Total permutations - (bad permutations of a[])-(bad permutations of b[])+(common bad permutations of {a[],b[]})
    n! - badA - badB + badAB
    */
    ll total = fact[n];
    total =((total - badA)%MOD2 +MOD2)%MOD2;
    total =((total - badB)%MOD2 +MOD2)%MOD2;
    total = (total + common)%MOD2;
    printint64(total);
    return 0;
}