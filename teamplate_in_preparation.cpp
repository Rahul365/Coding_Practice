#include<bits/stdc++.h>
#define removedups(v) sortvector(v); 
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
using namespace std;
const int maxn = 2e5+11;
using ll = long long int;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;
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

ll getans(ll x,ll y,ll a,ll b){
    if(x == y && !x){
        return 0;
    }

    if(x == y){
        return min(b*x, a * (x + y));
    }

    if(!x || !y) {
        return abs(x?x:y) * a; 
    }

    return min({
    a*(x + y),
    b*min(x,y) + (a * abs(x + y- (2*min(x,y)))),
    b*max(x,y) + (a * abs(x + y- (2*max(x,y))))
    });
}

int main(){
    int t;
    readint(t);
    while(t--){
        vector<ll> a(4);
        for(ll &x : a){
            readint64(x);
        }
        //Compute minimum amount needed to make x == 0 and y == 0
        printint64(getans(a[0],a[1],a[2],a[3]));
    }
    return 0;
}