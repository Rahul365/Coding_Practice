#include <bits/stdc++.h>
using ll = long long int;
using namespace std;

const ll MAXX = 1e18L + 1;
int main()
{
    int n;
    ll w;
    scanf("%d %lld", &n, &w);
    ll wt[n];
    int val[n];
    int sum_val = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i] >> val[i];
        sum_val += val[i];
    }

    //Now to achieve profit of value sum_val, using n items of weights and values
    //dp[item][profitval] = min weight of knapsack needed to fill to get a profit = profitval
    //dp[item][profitval] = minweight(using nth item , not using nth item)
    //dp[item][profitval] = minweight(dp[item-1][profitval - val[item]] + weight[item],dp[item-1][profitval]);
    ll dp[n + 1][sum_val + 1];
    dp[0][0] = 0; //0 profit using 0 items
    for (int i = 1; i <= n; i++)
        dp[i][0] = 0; //can achieve a profitvalue of 0 by using i items
    for (int j = 1; j <= sum_val; j++)
        dp[0][j] = MAXX; //can't achieve profitvalue of j with 0 items

    for (int item = 1; item <= n; item++)
    {
        for (int v = 1; v <= sum_val; v++)
        {
            dp[item][v] = dp[item - 1][v];
            if (val[item - 1] <= v && dp[item - 1][v - val[item - 1]] != MAXX)
            {
                dp[item][v] = min(dp[item][v], dp[item - 1][v - val[item - 1]] + wt[item - 1]);
            }
        }
    }
    ll ans = 0;
    for (int v = 1; v <= sum_val; v++)
    {
        if (dp[n][v] <= w)
        {
            ans = max(ans, (ll)v);
        }
    }
    printf("%lld \n", ans);
    return 0;
}