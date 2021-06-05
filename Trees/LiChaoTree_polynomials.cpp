#include <bits/stdc++.h>
#define removedups(v) \
    sortvector(v);    \
    v.resize(unique(v.begin(), v.end()) - v.begin());
#define USE_FILE(i, o)      \
    freopen(i, "r", stdin); \
    freopen(o, "w", stdout)
#define rint(x) scanf("%d", &x)
#define pint(x) printf("%d", x)
#define rint64(x) scanf("%lld", &x)
#define pint64(x) printf("%lld", x)
#define printpair(p) cerr << p.first << " " p.second << "\n"
#define sortvector(v) sort(v.begin(), v.end())
#define trace_vector(v)   \
    for (auto x : v)      \
        cerr << x << " "; \
    cerr << "\n";
using namespace std;
using ll = long long int;
using ull = unsigned long long int;
const int maxn = 2e5 + 11;
const int MAXN = 1e5 + 5;
const int LG = 20;
const int INF = 1e9;
const ll LINF = 1e19L;
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

struct point
{
    ll a;
    ll b;
    ll c;
    ll d;
    point()
    {
        b = c = d = 0;
        a = LINF;
    }
    point(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {}

    ll operator()(ll x)
    {
        return a + (b * x) + (c * x * x) + (d * x * x * x);
    }
};

const int N = 1e5 + 5;
const int M = 400;
vector<point> line(4 * N);
vector<ll> ans(M);

void add_line(point nw, int i = 0, int l = 0, int r = N)
{
    int m = l + (r - l) / 2;
    bool left = nw(l) < line[i](l);
    bool mid = nw(m + 1) < line[i](m + 1);

    if (mid)
    {

        swap(line[i], nw);
    }

    if (l == r)
        return;
    if (left != mid)
    {
        add_line(nw, 2 * i + 1, l, m);
    }
    else
    {
        add_line(nw, 2 * i + 2, m + 1, r);
    }
}

ll getMin(ll x, int i = 0, int l = 0, int r = N)
{
    if (l == r)
        return line[i](x);
    int mid = l + (r - l) / 2;
    if (x <= mid)
        return min(line[i](x), getMin(x, 2 * i + 1, l, mid));
    else
        return min(line[i](x), getMin(x, 2 * i + 2, mid + 1, r));
}

void init()
{
    fill(ans.begin(), ans.end(), LINF);
    fill(line.begin(), line.end(), point(LINF, 0, 0, 0));
}
// https://www.codechef.com/problems/POLY
int main()
{
    //cout << LINF <<"\n";
    /***
     - Preprocess answers for t in range[0,sqrt(1e5)]
     - 
     * */
    int t;
    rint(t);
    while (t--)
    {
        init();
        int n;
        rint(n);
        for (int i = 0; i < n; ++i)
        {
            ll a, b, c, d;
            scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
            point p(a, b, c, d);
            add_line(p, 0, M);
            for (int x = 0; x < M; ++x)
            {
                ans[x] = min(ans[x], p(x));
            }
        }

        int q;
        rint(q);
        while (q--)
        {
            ll t;
            rint64(t);
            /***
             Need to understand : Can't we answer each query on the go using LiChaoTree ?
             Since given polynomial is not represent any line rather it represent wave like graph on cartesian line.
             So any two polynomials p(a) & p(b) will have intersection point at (0,max value of x)
             and (sqrt(max value of x),0).
             So we'll have more than two intersections for any two polynomials.
             So for polynomial P(x) where x <= sqrt(max value of x), we can precompute the answer.
             and for polynomial P(x) where x > sqrt(max value of x) we are bound to have atmost 1 intersection.
             So we can use Li Chao tree to find the answer for such x. 

             let P(x) = P'(x);
             we'll have
             a1*x*x*x + b1* x * x  + c1 * x + d1 = a2*x*x*x + b2 * x * x + c2 * x + d2
             
             Since x >= 0 && x <= 1e5, negative value of x is not acceptable
             So minimum positive value of x, which will give us intersection between two polynomials can be found as

             ***/
            if (t < M)
                printf("%lld\n", ans[t]);
            else
                printf("%lld\n", getMin(t, 0, M)); //query t in range  [M,1e5]
        }
    }
    return 0;
}