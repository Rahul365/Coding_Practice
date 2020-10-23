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
template<typename T>
T pw(T a,T b){
    T r = 1;
    while(b){
        if(b&1) r = r * a;
        a = a*a;
        b >>= 1;
    }
    return r;
}

vector<int> getnumber(ll x){    
    vector<int> answer;
    while(x){
        answer.emplace_back(x%10);
        x/=10;
    }
    reverse(answer.begin(),answer.end());
    return answer;
}



ll countGoodNumbers(vector<int> num){
    ll answer = 0;
    int n = num.size();
    if(n<=1) return answer + (!n?0:num[0]);
    /*
    if(num[0] > num[n-1]){
        if((num[0]-1)!=0){
            answer = (num[0]-1) * pw<ll>(10LL,n-2);
        }
    }
    else if(num[0]<=num[n-1]){.....}
    */
    //2 _ _ _ _ 4 => 2 _ _ _ _ 2
    //best start is the number of this format : X_ _ _ _ _X etc.
    ll sub = 1/*for current number*/ + (num[0]-1>0?((num[0]-1) * pw<ll>(10LL,n-2)):0);
    for(int i = 1;i<n-1;++i){
        if(num[i] == 0) continue;/*No possibilities for this digit*/
        sub += (num[i] * pw<ll>(10LL,(ll)n-2-i));
    }
    answer = sub;
    for(int i = n-1;i>=1;--i){
        answer += 9LL * pw<ll>(10LL,max(0,i-2));
    }
    return answer;
}

//https://codeforces.com/problemset/problem/204/A
int main(){
    ll l,r;
    readint64(l);
    readint64(r);
    --l;
    vector<int> L = getnumber(l);
    vector<int> R = getnumber(r);
    /*Loops won't execute more than 9-10 times (Proof ?)*/
    while(r && R[0] != R.back()){
        R = getnumber(--r);
    }
    while(l && L[0] != L.back()){
        L = getnumber(--l);
    }
    /*To count the good numbers*/
    ll A = countGoodNumbers(R);
    ll B = countGoodNumbers(L);
    cerr << A << " " << B << " = " << (A-B)<<"\n";
    printint64(A-B);
    return 0;
}