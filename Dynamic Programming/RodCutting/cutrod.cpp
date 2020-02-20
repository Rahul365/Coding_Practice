#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4002;
int dp[MAXN];
int rodcut(int N, int *arr, int m, int cnt)
{
    if (N < 0) //if the rod is not properly cutted
        return 0;
    if (N == 0) //if the rod is properly cutted
        return cnt;
    int &ans = dp[N];
    if (ans != -1)
        return ans;
    ans = 0;
    for (int i = 0; i < m; i++)
    {
        if (N >= arr[i])
            ans = max(ans, rodcut(N - arr[i], arr, m, 1 + cnt));
    }

    return ans;
}

int rodcutII(int N, int *arr, int m)
{
    int dp[N + 1];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (dp[i] != -1 && i + arr[j] <= N)
                dp[i + arr[j]] = max(dp[i + arr[j]], 1 + dp[i]);
        }
    }
    return dp[N];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int m = 3;
        int arr[m];
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < m; i++)
        {
            cin >> arr[i];
        }
        sort(arr, arr + m);
        cout << rodcut(n, arr, m, 0) << "\n";
    }
}