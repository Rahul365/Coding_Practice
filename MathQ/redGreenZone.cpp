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

void addself(ll &a,ll b){
    a += b;
    if(a >= MOD1)
        a-=MOD1;
}

int n;
map<vector<vector<ll>>,ll> dp[maxn][4];
ll rec(vector<vector<ll>> pp,int color=3,int pos = 0){
    if(pos==n){
        return 1LL;
    }
    if(dp[pos][color].count(pp)){
        return dp[pos][color][pp];
    }
    ll &ans = dp[pos][color][pp];
    ans = 0LL;
    for(int curr = 0 ;curr < 3;++curr){
        if(pos == 0){
            addself(ans,rec(pp,curr,pos+1));
        }
        else{
            if(pp[color][curr]){
                --pp[color][curr];
                addself(ans,rec(pp,curr,pos+1));
                ++pp[color][curr];
            }
            else if(color == curr){
                addself(ans,rec(pp,curr,pos+1));
            }
        }
    }
    return ans;
}

int main(){
    readint(n);
    vector<vector<ll>> pp(3,vector<ll>(3));
    for(int i = 0;i<3;++i){
        for(int j =0;j < 3;++j){
            if(i == j) continue;
            readint(pp[i][j]);
        }
    }
    ll ans = rec(pp);
    printint64(ans);
    return 0;
}