#include <bits/stdc++.h>
using ll = long long int;
using namespace std;

const ll nax = 1e18L + 5;

int main()
{
    int n;
    scanf("%d", &n);
    ll a[n];
    ll sum[n + 1];
    sum[0] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }
    //sort(a,a+n);//use this if the relative order doesn't matter
    for(int i = 0;i<n;++i){
        sum[i + 1] = sum[i] + a[i];
    }

    ll dp[n][n];
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;
            dp[i][j] = nax;
            for (int k = i; k <= j - 1; k++)
            {
                // cout<<(sum[j+1]-sum[i])<<"\n";
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + (sum[j + 1] - sum[i]));
            }
        }
    }

    printf("%lld\n", dp[0][n - 1]);
    return 0;
}