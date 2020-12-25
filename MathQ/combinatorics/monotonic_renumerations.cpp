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
// https://codeforces.com/problemset/problem/1102/E

int main(){
    int n;
    readint(n);
    vector<ll> arr(n);
    map<ll,vector<int>> pos;
    for(int i = 0;i<n;++i){
      readint64(arr[i]);
      pos[arr[i]].emplace_back(i);
    }
    int start = pos[arr[0]].back();
    vector<int> mrk(n,1);
    for(int index : pos[arr[0]]){
        mrk[index] = 0;
    }
    /*
        b[] = {0,.......,end}
        b[] will consists of only 0's upto index i
        such that arr[i] = arr[0]
        Also upto index max(of all j's)(>i) such that arr[k] = arr[j] where 0<k<i
        Then b[0,...,j] = 0
        So we have to renumerate elements from index b[j+1,..,n-1]
        In total we have n-j-1 positions to fill.
        As per 3rd constraint, 
        b[i] == b[i+1] or b[i]+1 = b[i+1]
        As per 2nd constraint,
        if(a[i] == a[j]) then b[i] == b[j]
    */
    for(int i = 0;i<n;++i){
        if(!mrk[i]) continue;
        if(i <= start){
            mrk[i] = (i?mrk[i-1]:0);
            start = max(start,pos[arr[i]].back());
        }
        else{
            mrk[i] = mrk[i-1]+1;
            start = pos[arr[i]].back();
        }
    }
    trace_vector(mrk);
    // cerr << n-start-2 <<endl;
    ll answer = power<ll>(2LL,mrk.back(),MOD2);
    printint64(answer);
    return 0;
}