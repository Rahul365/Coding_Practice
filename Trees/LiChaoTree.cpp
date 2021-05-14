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
const ll LINF = 1e17L;
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
    ll x;
    ll y;
    point()
    {
        x = y = 0;
    }
    point(ll x, ll y) : x(x), y(y) {}
};

ll f(point a, ll x)
{
    return (a.x * x) + a.y;
}

const int N = 1e6 + 1;
vector<point> line(4 * N, point(0, LINF));

void add_line(point nw, int i = 1, int l = 1, int r = N)
{
    if (l > r)
        return;
    int m = l + (r - l) / 2;
    bool left = f(nw, l) < f(line[i], l);
    bool mid = f(nw, m + 1) < f(line[i], m + 1);
    if (mid)
    {
        swap(line[i], nw);
    }
    if (l == r)
        return;
    if (left ^ mid)
        add_line(nw, 2 * i, l, m);
    else
        add_line(nw, 2 * i + 1, m + 1, r);
}

ll getMin(ll x, int i = 1, int l = 1, int r = N)
{
    if (l > r)
        return LINF;
    int m = l + (r - l) / 2;
    if (l == r)
    {
        return f(line[i], x);
    }
    if (x < m)
    {
        return min(f(line[i], x), getMin(x, 2 * i, l, m));
    }
    return min(f(line[i], x), getMin(x, 2 * i + 1, m + 1, r));
}

ll sq(ll x)
{
    return x * x;
}
// https://atcoder.jp/contests/dp/tasks/dp_z
int main()
{
    int n;
    ll c;
    scanf("%d%lld", &n, &c);
    vector<ll> h(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld", &h[i]);
    }
    ll dp[n];
    memset(dp, 0LL, sizeof dp);
    auto Line = [&](int i)
    {
        return point(-2 * h[i], sq(h[i]) + dp[i]);
    };

    add_line(Line(0));
    for (int i = 1; i < n; ++i)
    {
        dp[i] = c + sq(h[i]) + getMin(h[i]);
        add_line(Line(i));
    }
    printf("%lld\n", dp[n - 1]);
    return 0;
}