#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d ",x)
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

ll fact[MAXN];
void computefact(){
    fact[0] = 1;
    for(ll i = 1;i < MAXN;++i){
        fact[i] = (fact[i-1] * i)%MOD1;
    }
}
ll ncr(ll n,ll r){
    if(n < r) return 0;
    ll answer = fact[n];
    answer = (answer * power<ll>(fact[r],MOD2-2LL,MOD2))%MOD2;
    answer = (answer * power<ll>(fact[n-r],MOD2-2LL,MOD2))%MOD2;
    return answer;
}

ll countMultiples(ll l, ll r,ll of){
    return (r/of) - (l-1)/of;
}
vector<vector<ll>> nCr(2002,vector<ll>(2002));
void computeCombinations(){
    nCr[0][0] = 1;//nCr(0,0)
    for(int n = 1;n<=1000;++n){
        nCr[n][0] = nCr[n][n] = 1;
        for(int r = 1;r < n;++r){
            nCr[n][r] = (nCr[n-1][r] + nCr[n-1][r-1]);
            if(nCr[n][r]>=MOD1){
                nCr[n][r]-=MOD1;
            }
            else if(nCr[n][r]<0){
                nCr[n][r]+=MOD1;
            }
        }
    }
}
// https://codeforces.com/problemset/problem/1433/E
int main(){
    // computefact();
    // computeCombinations();
    int n;
    readint(n);
    /*
        Answer = (n-1)!/(n/2);
        Why? 
        Two round dances are indistinguishable (equal) if one can be transformed to another by choosing the 
        first participant.
        For example, round dances [1,3,4,2], [4,2,1,3] and [2,1,3,4] are indistinguishable.
        So, the point is to choose disguinshable rounds otherwise we'll be counting repeated rounds 
        which are just are cycling permutation of some other indisguishable round.
        First we need to know how many distinguish cyclic permutations are there for n people's.
        Number of distinct cyclic permutations = (n-1)!;
        Now How many groups it is possible to divide these cyclic permutations into?
        As we can observe n is even, selecting more than n/2 bisecting point will just be repeting of some group which was already choosen earlier.
        e.g. n = 6
        let cyclic permutation be [1,2,3,4,5,6]
        Let's choose four heads such (n/2) consecutive elements starting from that head will form group for 1st round and rest for the second.
        head = 1, group1 = [1,2,3] and group2 = [4,5,6]
        head = 2, group1 = [2,3,4] and group2 = [5,6,1]
        head = 3, group1 = [3,4,5] and group2 = [6,1,2]
        Now let's choose head = 4
        head = 4, group1 = [4,5,6] and group1 = [1,2,3] -> which forms same dance groups as when head = 1.
        Thus only (n/2) starting points for groups are there.
        So our answer  =  (Total number of cyclic permutations)/(Number of heads which we can choose to divide these permutations into 2 indistinguishable groups)
        answer = (n-1)!/(n/2);
    */
    ll answer = 1;
    for(ll i = 2;i<n;++i)
    {
        if(i == n/2) continue;
        answer*=i;
    }   
    printint64(answer);
    return 0;
}