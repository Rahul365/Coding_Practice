#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

void maxself(ll &a, ll b)
{
    a = max(a, b);
}

void solveTLE(vector<int> &beauty, vector<int> &h)
{
    int n = h.size();
    vector<ll> dp(n);
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        dp[i] = beauty[i];
        for (int j = 0; j < i; j++)
        {
            if (h[i] > h[j] && dp[j] + beauty[i] > dp[i])
                dp[i] = dp[j] + beauty[i];
        }
        maxself(ans, dp[i]);
    }
}

const int maxn = 2e5 + 11;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> h(n);
    vector<ll> beauty(n);
    for (int &x : h)
    {
        scanf("%d", &x);
    }

    for (ll &x : beauty)
    {
        scanf("%lld", &x);
    }

    int base = pow(2, n - 1);

    vector<ll> tree(2 * base);
    //to find the maximal beauty sum of flowers such h[i] <= h[j]
    //height is monotonically increasing
    ll ans = 0;
    vector<ll> dp(n + 1);
    //dp[i] => stores the max sum of flowers such that last element was at height i

    for (int flower = 0; flower < n; flower++)
    {
        //for flower x ,
        // i want to know the max dp[i] where i lies in range[0,h[flower]-1]
        ll best = 0;
        int x = h[flower] + base;
        while (x > 1)
        {
            if (x & 1)
            {
                maxself(best, tree[x - 1]);
            }
            x >>= 1;
        }
        dp[h[flower]] = best + beauty[flower];
        for (int i = base + h[flower]; i >= 1; i >>= 1)
        {
            maxself(tree[i], dp[h[flower]]);
        }
        //~ for (int i = 0; i < h[flower]; i++){
        //~    maxself(dp[h[flower]], dp[i] + beauty[flower]);
        //~ }
    }

    for (int flower = 0; flower < n; flower++)
    {
        maxself(ans, dp[h[flower]]);
    }
    printf("%lld\n", ans);

    return 0;
}