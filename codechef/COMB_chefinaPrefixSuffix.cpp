#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9L + 7;
const int MAXN = 1e5 + 1001;
ll fact[MAXN], invfact[MAXN];

void multiply_self(ll &a, ll b)
{
    a = (a * b);
    if (a >= mod)
        a %= mod;
}

ll power(ll x, ll y)
{
    ll r = 1LL;
    while (y)
    {
        if (y & 1LL)
            multiply_self(r, x);
        multiply_self(x, x);
        y >>= 1LL;
    }
    return r;
}

//for computing inverse factorials
ll invfacts(ll x)
{
    return power(x, mod - 2);
}
//for computing factorials of number
void computefact()
{
    fact[0] = 1LL;
    invfact[0] = 1LL;
    for (int i = 1; i < MAXN; i++)
    {
        fact[i] = (fact[i - 1] * i) % mod;
        invfact[i] = invfacts(fact[i]);
    }
}

ll x[2 * MAXN];
vector<int> reps;
int main()
{
    int t;
    scanf("%d", &t);
    computefact();
    while (t--)
    {
        int n;
        scanf("%d", &n);
        ll total = 0;
        for (int i = 1; i <= 2 * n; i++)
        {
            scanf("%lld", &x[i]);
            total += x[i];
        }
        //insert two 0's
        int N = 2 * n + 3;
        x[2 * n + 1] = 0;
        x[2 * n + 2] = 0;
        sort(x + 1, x + N);
        //compute ((N-1)! * (2^(N-1-ym))/(y1! * y2! * y3! * ... * ym!);

        ll sum = total / (ll)(n + 1);

        ll ans = fact[n - 1];

        int skip0s = 2; //for two newly inserted 0's
        bool first = true;
        pair<ll, ll> curr;

        ll swappablecoef = 1;

        reps.clear();

        for (int i = 1; i <= n + 1; i++)
        {
            //pair  x[i] & x[2*n+3- i]
            ll left = x[i];
            ll right = x[N - i];

            if (left + right != sum)
                ans = 0;

            if (!left || !right)
                if (skip0s > 0)
                {
                    skip0s--;
                    continue;
                }

            if (first)
                curr = make_pair(left, right);
            if (first || curr != make_pair(left, right))
            {
                curr = make_pair(left, right);
                reps.push_back(1);
            }
            else
                reps.back()++;

            if (first)
                first = false;

            if (left != right)
            {
                multiply_self(swappablecoef, 2LL);
            }
        }

        if (skip0s > 0)
            ans = 0;

        for (size_t i = 0; i < reps.size(); i++)
        {
            multiply_self(ans, invfact[reps[i]]);
        }
        multiply_self(ans, swappablecoef);
        printf("%lld\n", ans);
    }
    return 0;
}