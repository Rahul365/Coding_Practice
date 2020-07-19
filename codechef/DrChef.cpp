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


void solve(){
    int n;
    ll x;
    readint(n);
    readint64(x);
    vector<ll> a(n);
    for(int i = 0;i<n;++i)
        readint64(a[i]);
    sortvector(a);
    // reverse(a.begin(),a.end());
    //a[0]==a[1]==......==a[n-1]
  
    if(x  >= a[n-1]){
        //if the number of cures is >= maximum populated country
        // then all the countries can be cured in N days
        printint(n);
        printf("\n");
        return;
    }
    //sort the countries by their population and try maximizing the value of x 
    //without wasting any number of days
    //To avoid wasting days , we can cure some countries while maximizing the value of x
    //if a[i] <= x, then we can cure this country without wasting days
    int days = 0;
    int cured = 0;
    int i = -1;
    while(i+1 < n){
        //find such point where a[i] <= x && x < a[i+1]
        if(x >= a[i+1]){
            ++i; continue;
        }

        //since a[i] <= x, so 2*a[i] > x
        if(i>=0 && 2*a[i] > x){
            x = a[i]*2;
            ++days;
            ++cured;
            continue;
        }

        if(i+1 == n-1){
            //if this is the last country deliver till x < a[n-1]
            while(x < a[n-1]){
                x*=2;
                ++days;
            }
            //Now cure last country and break 
            ++days;
            ++cured;
            break;
        }
        if(i+1!=n-1 && 2*x <= a[n-1]){
            //deliver to last country and double x
            x*=2;
            ++days;
            continue;
        }
        //x exceed the max population
        //So the number of days to cure will be remaining countries + 1
        //Since if x is doubled once again , it will be greater than max populated country
        //So (n-1)th country + remaining countries will left to cure and can be done in equal number of days
        if(i+1!=n-1 && 2*x > a[n-1]){
            ++days;
            break;
        }
    }
    printint(days+(n-cured));
    printf("\n");
}

int main(){
    int T;
    readint(T);
    while(T--){
        solve();
    }
    return 0;
}