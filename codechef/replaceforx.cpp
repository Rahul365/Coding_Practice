#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define printintln(x) printf("%d\n",x)
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
// https://www.codechef.com/OCT20A/problems/REPLESX
int getanswer(vector<int> &arr,int N,int x,int p,int k){
// p-> target position for which we want to make arr[p] = x;
// k-> field of operation where we can convert kth smallest number to any other number.
sortvector(arr);
// trace_vector(arr);
auto getLTX = [&](){
    for(int i = N;;--i){
        if(arr[i] >= x) continue;
        return i;
    }
    return 0;
};

auto getGTX =[&](){
    for(int i = 1;i<=N;++i){
        if(arr[i] <= x) continue;
        return N-i+1;
    }
    return 0;
};
if(arr[p] == x) return 0;//already correct value,no operations needed
if(k == p) {
	if(x == arr[k]){ return 0;}
	if(x > arr[k]){ return getLTX() - k + 1;}
	if(x < arr[k]){ return getGTX() - (N-k);}
}
if(k < p){
	if(x == arr[k]){ return -1; /*not possible as */ }
	if(x > arr[k]){
        if(x < arr[p]) return -1;
        return getLTX() - p+1;    
    }
	if(x < arr[k]){  return -1;/*x can't be pushed further kth position*/}
}
if(p < k){
	if(x == arr[k]){ return -1;/*not possible*/}
	if(x > arr[k]){  return -1;}
	if(x < arr[k]){
          if(x > arr[p]) return -1; 
        //   /*Availability of x before p*/
        //   bool ok = false;
        //   for(int i = 1;i<p;++i) if(arr[i] == x){
        //       ok = true;
        //       break;
        //   }
        //   if(!ok) return -1;
          return getGTX() - (N-p);
    }
}
return -1;
}

int main(){
    int T;
    readint(T);
    while(T--){
        int n,x,p,k;
        readint(n);
        readint(x);
        readint(p);
        readint(k);
        vector<int> arr(n+1);
        for(int i = 1;i<=n;++i) readint(arr[i]);
        printintln(getanswer(arr,n,x,p,k));
    }
    return 0;
}