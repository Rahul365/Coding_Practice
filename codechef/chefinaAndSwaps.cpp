#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
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
T power(T a,T b,T mod){
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
template<typename T>
T power(T a,T b){
    T r = 1;
    while(b){
        if(b&1){
            r = r*a;
        }
        a *= a;
        b >>= 1;
    }
    return r;
}
/*compute inversions*/
void inversions()
{
    inv = new ll[maxn];
    inv[0]= 0;
    for(ll i = 1;i<maxn;++i){
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


ll T[maxn] = {0LL};
ll fa[maxn] = {0LL};
ll fb[maxn] = {0LL};
bool okA,okB;
vector<ll> c;

void compressValues(vector<ll> &a,vector<ll> &b){
    for(ll v : a) c.push_back(v);
    for(ll v : b) c.push_back(v);
    removedups(c);
    auto findpos=[&](ll k){
        ll l = 0;
        ll r = (int)c.size() - 1;
        while(l<=r){
            ll m = l+(r-l)/2;
            if(c[m] == k) return m;
            if(c[m] > k){
                r = m-1;
            }
            else{
                l = m+1;
            }
        }
        return -1LL;
    };
    for(ll &v : a) v = findpos(v);
    for(ll &v : b) v = findpos(v); 
}


void fix(set<ll> &A,set<ll> &B, ll &cost,ll &mn){
     /*
            Fix those elements which have frequency more than half in x

        */
    while(!A.empty() && !B.empty()){
            auto ta = A.begin();
            ll g1 = fa[*ta]-(T[*ta]>>1);
            while(g1 && !B.empty()){
                auto nb = B.rbegin();
                ll gg = fb[*nb] - (T[*nb]>>1);
                if(gg == 0){
                    B.erase(prev(B.end()));
                }
                else{
                    ll rm = min(g1,gg);
                    fa[*ta] -= rm;
                    fb[*ta] += rm;
                    fa[*nb] += rm;
                    fb[*nb] -= rm;
                    g1-=rm;
                    gg-=rm;
                    cost += min((rm + rm) * mn,rm * c [min(*ta,*nb)]);
                }
            }
            A.erase(ta);
    }
}



void solve(){
    int n;
    readint(n);
    vector<ll> a(n),b(n);
    c.clear();
    memset(fa,0LL,sizeof fa);
    memset(fb,0LL,sizeof fb);
    memset(T,0LL,sizeof T);
    for(int i = 0;i<n;++i){
        readint64(a[i]);
    }
    for(int i = 0;i<n;++i){
        readint64(b[i]);
    }
    compressValues(a,b);
    const int m = (int)c.size();
    bool ok = true;
    for(int i = 0;i<n;++i){
        ++T[a[i]]; ++fa[a[i]];
        ++T[b[i]]; ++fb[b[i]];
    }

    for(int i = 0;i<m;++i){
        if(T[i]&1LL){
            ok = false;
            break;
        }
    }

    
    //Now cost of swap will be c[min(a[i],b[i])]
    if(!ok){
        printf("-1\n");
    }
    else{
        ll cost = 0LL;
        set<ll> A,B;
        for(ll v : a) if(fa[v]-(T[v]>>1) > 0) A.insert(v);
        for(ll v : b) if(fb[v]-(T[v]>>1) > 0) B.insert(v);
        ll mn = c[0];
        fix(A,B,cost,mn);
        printf("%lld\n",cost);
        // for(ll i = 0 ;i<m;++i){
        //     cerr << fa[i] << " " << fb[i] <<"\n";
        // }
    }
}

int main(){
    USE_FILE("inputchefinaandswaps.txt","outputchefinaandswaps.txt");
    int T;
    readint(T);
    while(T--){
        solve();
    }
    return 0;
}