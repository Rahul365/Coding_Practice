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
    inv = new ll[MAXN*10];
    inv[0]= 0;
    for(int i = 1;i<MAXN*10;++i){
        inv[i] = power((ll)i,MOD2-2LL,MOD2);
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
void multiply(T &a,T b){
    a = (1LL * a * b)%MOD2;
}

template<typename T>
void addself(T&a,T b){
    a = (a + b);
    if(a >= MOD2) a-=MOD2;
    else if(a < 0) a+=MOD2;
}

char str[100007];
// https://codeforces.com/contest/364/problem/A
int main()
{
    int a;
    scanf("%d",&a);
    scanf("%s",&str[0]);
    int n=0;
    for(;str[n]!='\0';++n);
    int arr[n];
    memset(arr,0,sizeof arr);
    for(int i = 0;i<n;++i) arr[i] += str[i]-'0' + (i?arr[i-1]:0);
    unordered_map<int,int> freq;
    for(int i = 0;i<n;++i)for(int j = i;j<n;++j){
        ++freq[arr[j]-(i?arr[i-1]:0)];
    }
    /*
        Basic idea is that the sum of rectangle represented by top left(x1,y1) and bottom right(x2,y2)
        can be computed by using the expression sum(x1,x2)*sum(y1,y2);
        where sum(l,r) = s[l] + s[l+1] +......+ s[r].
        This property of rectangle is applicable only where
        mat[i][j] = s[i] * s[j]; where s[] is linear array of n elements.
        e.g. [
            1,2,3,4
            2,4,6,8
            3,6,9,12
            4,8,12,16
        ]
        exploiting above property of this special matrix, we need to find rectangles for which
        sum(x1,x2) * sum(y1,y2)==a
        So our algo will be like this, 
        1) compute sum for every segment sum(l,r) and count freq for every sum of the segment.
        2) then iterate over every segment and do this:
           if(sum(l,r)!=0 && sum(l,r)<=a && a%sum(l,r)==0){
               answer += freq[a/sum(l,r)];
           }
        3) print answer;
        Base case is for a = 0, we have to handle it differently.
    */
    ll answer = 0;
    if(!a){
        /*
            when a = 0,
            then we are only interested int pairs of the form sum(x1,x2) * sum(y1,y2) where either one of the factor is 0
            let f(0) be the number of segments with sum == 0.
            Then #of ways that first factor is zero = f(0)*(total #of segments in the string);
            and #of ways that second factor is zero = (total #of segments in the string)*f(0);
            Also we don't need both the factors to be zero 
            #of ways that both factor can be zero = f(0)*f(0);
            So total number of rectangles with sum == 0 = (#of ways that first factor is zero) + (#of ways that second factor is zero) - (#of ways that both factor can be zero)
        */
        answer = 1LL*freq[0]*((1LL*n*(n+1)) - 1LL*freq[0]);
    }
    else{
        for(int i = 0;i<n;++i)for(int j = i;j<n;++j){
            int sum = arr[j]-(i?arr[i-1]:0);
            if(sum && a>=sum && a%sum==0){
                answer += freq[a/sum];
            }
        }
    }
    printf("%I64d",answer);
    return 0;
}