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
    return r%mod;
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

template<typename T>
void addself(T &a,T b){
    a = (a + b)%MOD1;
}

class BIT{
    vector<int> a;
    public:
    BIT(int n){
        a = vector<int>(n+1);
    }

    void update(int index,int val){
        for(++index ; index <(int)a.size();index+=index&(-index)){
            a[index]+=val;
        }
    }

    int range(int l,int r){
        return read(r) - read(l-1);
    }
    int read(int pos){
        int sum = 0;
        ++pos;
        while(pos > 0){
            sum += a[pos];
            pos -= pos&(-pos);
        }
        return sum;
    }
};

template<typename T>
T ncr(T n,T r){
    if(n < r) return 0;
    if(n == r) return 1;
    T p = 1,k=1;
    while(r){
        p *= n;
        k *= r;
        T d = gcd(p,k);
        p/=d;
        k/=d;
        --n;
        --r;
    }
    return p;
}

//TODO
int main(){
    int t;
    readint(t);
    while(t--){
        int n;
        readint(n);
        vector<int> a(n);
        vector<int> F(n+1);
        for(int i = 0;i<n;++i){
             readint(a[i]);
             ++F[a[i]];
        }
        /**
         * Idea : 
         * For every 1<=x<=N, let's count it's frequency as F[x]
         * for every x
         *   answer[x] = (sum of sequences for every 1<=fx<=F[x])
         * 
         */
        vector<vector<ll>> dp(n+1,vector<ll>(n+1,0LL));
        //dp[x][fx]=>number of sequences in which the frequency of x is fx
        for(int x = 1;x<=n;++x){
            for(int f = 1;f <= F[x];++f){
                dp[x][f] = 1;
            }
        }
        for(int x = 1;x<=n;++x){
            for(int f = 1;f<=F[x];++f){
                addself(dp[x][f],dp[x][f-1]);
                for(int a = 1; a< x;++a){
                    addself(dp[x][f],dp[a][min(F[a],f-1)]);
                }
                for(int b = x+1;b <=n;++b){
                 addself(dp[x][f],dp[b][min(F[b],f)]);
                }
            }
        }
        vector<ll> answer(n+1);
        for(int x = 1;x <= n;++x){
            answer[x] = 0;
            for(int f = 1;f <= F[x];++f){
                addself(answer[x],dp[x][f]);
            }
        }
        for(int i = 0;i<n;++i){
            printf("%d ",answer[a[i]]);
            answer[a[i]]=0;
        }
        printf("\n");
    }
    return 0;
}