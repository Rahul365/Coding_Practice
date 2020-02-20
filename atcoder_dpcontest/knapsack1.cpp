#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;

ll memo[101][100001];
ll knapsack(int W, int n, int *wt, ll *val)
{
    ll &ans = memo[n][W];
    if (ans != -1)
        return ans;
    if (n == 0 || W == 0)
        return ans = 0;
    ans = knapsack(W, n - 1, wt, val);
    if (W >= wt[n - 1])
        ans = max(ans, val[n - 1] + knapsack(W - wt[n - 1], n - 1, wt, val));
    return ans;
}

int knapsackdp(int W, int n, int *wt, ll *val)
{
    ll dp[n + 1][W + 1];
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int w = 0; w <= W; w++)
        dp[0][w] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= W; w++)
        {
            dp[i][w] = dp[i - 1][w];
            if (w >= wt[i - 1])
                dp[i][w] = max(dp[i][w], val[i - 1] + dp[i - 1][w - wt[i - 1]]);
        }
    }

    return dp[n][W];
}

int main()
{
    memset(memo, -1, sizeof memo);
    int n, w;
    cin >> n >> w;
    int wt[n];
    ll val[n];
    for (int i = 0; i < n; i++)
        cin >> wt[i] >> val[i];
    cout << knapsackdp(w, n, wt, val) << "\n";
    return 0;
}