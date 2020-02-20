#include <bits/stdc++.h>
using ll = long long int;
using namespace std;

ll game(ll *arr, int n)
{
    ll dp[n][n];
    for (int i = 0; i < n; i++)
        dp[i][i] = arr[i];

    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;
            if (len == 2)
            {
                dp[i][j] = max(dp[i][i], dp[j][j]);
            }
            else
            {
                dp[i][j] = max(arr[i] + min(dp[i + 1][j - 1], dp[i + 2][j]), arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2]));
            }
        }
    }
    return dp[0][n - 1];
}

int main()
{
    int n;
    scanf("%d", &n);

    ll a[n];
    ll total = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
        total += a[i];
    }

    ll x = game(a, n);
    ll y = total - x;
    ll ans = x - y;
    printf("%lld\n", ans);
    return 0;
}