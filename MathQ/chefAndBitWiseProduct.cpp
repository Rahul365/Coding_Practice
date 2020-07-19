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
//MAY LONG CHALLENGE 2020 : ALMOST PARTICIPATED BUT I'LL PASS THIS ONE
template<typename T>
T power(T x,T y){
    T r = 1;
    while(y){
        if(y&1){
            r = (r * x);
        }
        x = x*x;
        y >>= 1;
    }
    return r;
}


ll lastbit(ll n){
    ll pos = 0;
    while(n){
        ++pos;
        n >>= 1;
    }
    return pos;
}

void dobest(pair<ll,ll> &best,ll x,ll y,ll l,ll r,ll val,ll end,vector<ll> bin){
    if(l<=val && val <= r){
        if(best.first < (x&val)*(y&val))
        {
            best.first = (x&val)*(y&val);
            best.second = val;
        }
        if(x&val==0 || y&val == 0){
            return;
        }
    }
    if(val > r) return;
    if(!end) return;
    bin[end-1] = 1;
    dobest(best,x,y,l,r,val + power(2LL,end-1LL),end-1,bin);
    bin[end-1] = 0;
    dobest(best,x,y,l,r,val,end-1,bin);
}

void solve(ll x,ll y,ll l,ll r){
    vector<ll> bin(100,0);
    pair<ll,ll> best = {0,0};
    ll end = lastbit(max(l,r));
    dobest(best,x,y,l,r,0,end,bin);
    printint64(best.second);
}

/**
 *  Maximize product (x&z)*(y&z)  such that  l <= z <= r
 **/
int main(){
    vector<ll> ranges;
    ranges.push_back(0);
    for(ll i = 0;i<=100;++i) 
        ranges.push_back(power(2LL,i));

    int t;
    readint(t);
    while(t--){
        ll x,y,l,r;
        readint64(x);
        readint64(y);
        readint64(l);
        readint64(r);
        if(!x || !y) { printf("0\n"); continue;} 
        //l = 0 and r >= 2*max(x,y) , there will always be a z which can preserve maximum set bits of both x and y
        //and maximize product (x&z)*(y&z)
        /*
        pair<ll,ll> best;
        while(l<=r)
        {
            if((x&l)*(y&l) > best.first){
                best.second = l;
            }
            ++l;
        }
        printint64(best.second);
        */
        solve(x,y,l,r);
        printf("\n");
    }
    return 0;
}