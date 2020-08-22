#include <bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(), v.end()) - v.begin());
#define USE_FILE(i, o) freopen(i, "r", stdin); freopen(o, "w", stdout)
#define readint(x) scanf("%d", &x)
#define printint(x) printf("%d", x)
#define readint64(x) scanf("%lld", &x)
#define printint64(x) printf("%lld", x)
#define printpair(p) cerr << p.first << " " p.second << "\n"
#define sortvector(v) sort(v.begin(), v.end())
#define trace_vector(v)    for (auto x : v)cerr << x << " ";cerr << "\n";
using namespace std;
const int maxn = 2e5 + 11;
const int MAXN = 1e5 + 5;
const int LG = 20;
using ll = long long int;
const ll INF = 1e15;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;
ll *inv;
/*compute x^y*/
template <typename T>
T power(T a, T b, T mod = MOD1)
{
    T r = 1LL;
    while (b)
    {
        if (b & 1LL)
        {
            r = (r * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1LL;
    }
    return r;
}
/*compute inversions*/
void inversions()
{
    inv = new ll[maxn];
    inv[0] = 0;
    for (int i = 1; i < maxn; ++i)
    {
        inv[i] = power((ll)i, MOD1 - 2LL);
    }
}

/*compute gcd(a,b)*/
template <typename T>
T gcd(T a, T b)
{
    while (b)
    {
        T t = b % a;
        a = b;
        b = t;
    }
    return a;
}

void compress(vector<int> &a)
{
    vector<int> b = a;
    removedups(b);
    auto findpos = [&](int key) {
        int l = 0;
        int r = b.size() - 1;
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (key == b[m])
            {
                return m;
            }
            if (key > b[m])
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return -1;
    };
    for (int i = 0; i < a.size(); ++i)
        a[i] = findpos(a[i]);
}


// ll dp[1002][1002];
// https://www.codechef.com/AUG20A/problems/CHEFWED
int main()
{
    int t;
    readint(t);
    while (t--)
    {
        int n;
        ll k;
        readint(n);
        readint64(k);
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            readint(a[i]);
        //number of guests seating at the same table and they will argue
        //at least n table could be bought
        //TLE error , no need for two dimensions , table is just a table
        // for(int i = 0;i<n+2;++i) for(int j= 0;j<n+2;++j) dp[i][j] = INF;
        /*
        function<ll(int,int)> rec = [&](int pos,int table){
            ll &ans = dp[pos][table];
            if(ans!=INF) return ans;
            ll arg = k;
            ll cnt[105];
            memset(cnt,0LL,sizeof cnt);
            for(int i = pos;i<n;++i){
                if(++cnt[a[i]]>=2) arg += 1 + (cnt[a[i]]==2);
                ans = min(ans,arg + (i+1==n?0:rec(i+1,table+1)));
            }
            return ans;
        };
        */
       
        ll cnt[105];
       /*
        for(int table = n-1;table>=0;--table){
            for(int i = 0;i<n;++i){
                ll arg = k;
                memset(cnt,0LL,sizeof cnt);
                for(int j = i;j<n;++j){
                    if(++cnt[a[j]]>=2) arg += 1 + (cnt[a[j]]==2);
                    dp[i][table] = min(dp[i][table],arg + (j+1==n || table+1==n?0:dp[j+1][table+1]));
                }
            }
        }
    */
        vector<ll> dp2(n+1,-1);
        function<ll(int)> rec = [&](int pos){
            if(pos == n){
                return 0LL;
            }
            ll &ans = dp2[pos];
            if(ans!=-1) return ans;
            ans = INF;
            ll cnt[105];
            memset(cnt,0LL,sizeof cnt);
            ll arg = k;
            for(int i = pos;i<n;++i){
                if(++cnt[a[i]]>1) arg += 1 + (cnt[a[i]]==2);
                ans = min(ans,arg + rec(i+1));
            }
            return ans;
        };

        dp2[n] = 0LL;//base case
        for(int pos = n-1;pos>=0;--pos){
            dp2[pos] = INF;
            ll arg = k;
            memset(cnt,0LL,sizeof cnt);
            for(int i = pos;i<n;++i){
                if(++cnt[a[i]]>1) arg += 1 + (cnt[a[i]]==2);
                dp2[pos] = min(dp2[pos],arg + dp2[i+1]);
            }
        }
        ll ans = dp2[0];//rec(0);
        printint64(ans);
        printf("\n");
    }
    return 0;
}