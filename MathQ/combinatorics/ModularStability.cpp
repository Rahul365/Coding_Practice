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

ll fact[MAXN * 5];
void computefact(){
    fact[0] = 1;
    for(ll i = 1;i < MAXN *5;++i){
        fact[i] = (fact[i-1] * i)%MOD2;
    }
}
ll ncr(ll n,ll r){
    if(n < r) return 0;
    ll answer = fact[n];
    answer = (answer * power<ll>(fact[r],MOD2-2LL,MOD2))%MOD2;
    answer = (answer * power<ll>(fact[n-r],MOD2-2LL,MOD2))%MOD2;
    return answer;
}


void test(){
    /*Conclusion for this Stable Modularity property, all numbers in the array should be multiple of smallest element in the array*/
    vector<int> arr({3,9,6,12,36});
    for(int num = 123;num <=124254;++num){
        int val = num;
        for(int m : arr) val %= m;
        do{
            int tmp  =num;
            for(int m : arr) tmp%=m;
            if(tmp!=val){ 
                cerr <<"For X = " << num << " ";
                for(int m : arr ) cerr << m <<" "; cerr<<"\n";
            }
        }while(next_permutation(arr.begin(),arr.end()));
        reverse(arr.begin(),arr.end());
    }
}

ll countMultiples(ll l, ll r,ll of){
    return (r/of) - (l-1)/of;
}
// https://codeforces.com/problemset/problem/1359/E
int main(){
    computefact();
    int n,k;
    readint(n);
    readint(k);
    ll answer = 0;
    for(int i = 1;i<=n;++i){
        ll N = countMultiples(i+1,n,i);
        if(N>=k-1){
            answer = (answer + ncr(N,k-1))%MOD2;
        }
    }
    printint64(answer);
    return 0;
}