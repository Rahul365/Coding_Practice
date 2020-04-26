#include<bits/stdc++.h>
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d ",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld\n",x)
#define sortvector(v) sort(v.begin(),v.end())
using namespace std;
const int maxn = 2e5+11;
using ll = long long int;
const ll mod = 998244353;
template<typename T>
T power(T a,T b){
   T r = 1LL;
   while(b){
       if(b&1LL){
           r = (r * a)%mod;
       }
       a = (a*a)%mod;
       b >>= 1LL;
   } 
   return r;
}

template<typename T>
void multiply(T &a, T b){
    a = (a * b);
    if(a >= mod) a %= mod;
}

ll two[maxn];
ll frq[maxn];
ll after[maxn];//elements greater than current current mex
int main(){
    two[0] =1LL;
    for(int i = 1;i<maxn;++i) two[i] = (2*two[i-1])%mod;
    int t;
    readint(t);
    while(t--){
        int n;
        readint(n);
        for(int i = 0;i<=n+70;++i) frq[i] = after[i] = 0;
        for(int i = 0;i<n;++i){
            ll x;
            readint64(x);
            ++frq[min(x,n+1LL)];
        }
        // for(int i = n+68;i>0;--i){
        //     after[i] = frq[i] + after[i+1];
        // }
        ll ans = 0;
        ll ways = 1LL;
        ll left = n;
        for(ll i = 1;i<=n+1 && ways;++i){//Suppose i is the current mex value
            //if i can't afford to be in contiguous subsequence 
            //and it's frequency is 0
            //then it contributes 0 number of subsequences to the answer
            left -= frq[i];
            ans = (ans + i * (ways * power(2LL,left)%mod))%mod;
            ways = ways * (power(2LL,frq[i])-1)%mod;
        }
        ans = (ans + mod)%mod;
        printint64(ans);
    }
    return 0;
}