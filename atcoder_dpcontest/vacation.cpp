#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> memo;
int maxhappiness(vector<vector<int>> &h, int n, int prev_activity)
{
    int &ans = memo[n][prev_activity];
    if (ans != -1)
        return ans;
    if (n == 0)
        return ans = 0;
    ans = 0;
    for (int i = 0; i < 3; i++)
    {
        if (prev_activity == i)
            continue;
        ans = max(ans, h[n - 1][i] + maxhappiness(h, n - 1, i));
    }
    return ans;
}

int maxhappinessutil(vector<vector<int>> &h, int n)
{
    int ans = 0;
    for (int i = 0; i < 3; i++)
        ans = max(ans, maxhappiness(h, n, i));
    return ans;
}

int maxhappiness(vector<vector<int>> &h, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    dp[0][0] = 0;
    //no vacation no activity
    for (int v = 1; v <= n; v++) //vacations
    {
        for (int activity = 0; activity < 3; activity++)
        {
            //last activity in previous day was activiy
            if (v == 1)
                dp[v][activity] = h[v - 1][activity];
            else
            {
                for (int j = 0; j < 3; j++) //today's activity
                    if (activity != j)      //can't perform the same activity
                        dp[v][activity] = max(dp[v][activity], h[v - 1][activity] + dp[v - 1][j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 3; i++)
        ans = max(ans, dp[n][i]);
    return ans;
}

int main()
{
    int n;
    cin >> n;
    memo = vector<vector<int>>(n + 1, vector<int>(3, -1));
    vector<vector<int>> hps(n, vector<int>(3, 0)); //happiness points
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> hps[i][j];
    }
    //objective is to gain maximum happiness points here
    //each activity can't be done for two or more consecutive days
    cout << maxhappinessutil(hps, n) << "\n";
    return 0;
}