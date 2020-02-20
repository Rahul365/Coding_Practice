#include <bits/stdc++.h>
using namespace std;

/*O(k*n*n)*/
int stocksI(int *prices, int n, int k)
{
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));

    for (int i = 1; i <= k; i++)
    {
        for (int d = 1; d < n; d++)
        {
            dp[i][d] = dp[i][d - 1];
            for (int j = 0; j < d; j++)
                dp[i][d] = max(dp[i][d], prices[d] + dp[i - 1][j] - prices[j]);
        }
    }

    for (int i = 0; i <= k; i++)
    {
        for (int d = 0; d < n; ++d)
            cout << dp[i][d] << " ";
        cout << "\n";
    }
    return dp[k][n - 1];
}

void printtrace(const vector<vector<int>> &dp, int *prices, int d, int k)
{
    if (k == 0 || d == 0)
        return;
    while (dp[k][d - 1] == dp[k][d])
        --d;

    int maxdiff = dp[k][d] - prices[d];
    for (int i = d - 1; i >= 0; i--)
    {
        if (maxdiff == dp[k - 1][i] - prices[i])
        {
            cout << "Buy on day : " << i << " | Sell on day : " << d << " | profit : " << (prices[d] - prices[i]) << "\n";
            k = k - 1;
            d = i - 1;
            break;
        }
    }
    printtrace(dp, prices, d, k);
}

void printtracelinear(const vector<vector<int>> &dp, int *prices, int d, int k)
{
    stack<pair<int, int>> stk;
    while (true)
    {
        if (k == 0 || d == 0)
        {
            break;
        }
        if (dp[k][d - 1] == dp[k][d])
        {
            d = d - 1;
        }
        else
        {

            int maxdiff = dp[k][d] - prices[d];
            for (int i = d - 1; i >= 0; i--)
            {
                if (maxdiff == dp[k - 1][i] - prices[i])
                {
                    stk.push({i, d}); //buy stock on ith day and sell it on dth day
                    d = i - 1;
                    k = k - 1;
                    break;
                }
            }
        }
    }

    while (!stk.empty())
    {
        int buy = stk.top().first;
        int sell = stk.top().second;
        cout << "Buy on day : " << (buy + 1) << " | Sell on day : " << (sell + 1) << " | profit = " << (prices[sell] - prices[buy]) << "\n";
        stk.pop();
    }
}

void printdp(vector<vector<int>> &dp, int k, int n)
{
    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
            cout << dp[i][j] << " ";
        cout << "\n";
    }
}

/*O(k*n)*/
int stocksII(int *prices, int n, int k)
{
    if (!n)
        return 0;
    if (k > n)
        k = n / 2;
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));

    for (int i = 1; i <= k; i++)
    {
        int maxdiff = dp[i - 1][0] - prices[0];
        for (int d = 1; d < n; d++)
        {
            dp[i][d] = dp[i][d - 1];
            dp[i][d] = max(dp[i][d], prices[d] + maxdiff);

            maxdiff = max(maxdiff, dp[i - 1][d] - prices[d]);
        }
    }

    int D = n - 1;
    int K = k;
    while (dp[K - 1][D] == dp[K][D])
        --K;
    printtracelinear(dp, prices, D, K);
    printdp(dp, k, n);

    return dp[k][n - 1];
}

/*Time : O(k*n) , space : O(2*n)*/
int maxprofit(int *prices, int n, int k)
{
    if (!n)
        return 0;
    if (k > n / 2)
        k = n / 2;

    vector<vector<int>> dp(2, vector<int>(n, 0));

    for (int t = 1; t <= k; t++)
    {
        int p_t = (t + 1) % 2; //previous transaction
        int c_t = t % 2;       //current transaction
        int maxdiff = dp[p_t][0] - prices[0];
        for (int d = 1; d < n; d++)
        {
            dp[c_t][d] = max(dp[c_t][d - 1], prices[d] + maxdiff);
            maxdiff = max(maxdiff, dp[p_t][d] - prices[d]);
        }
    }

    return dp[k % 2][n - 1]; //maximum profit acheivable by doing atmost k transactions
}

int main()
{
    //n -> number of days
    //k -> number of transactions
    //transactions are isolated
    //no stock can be bought and sell on the same day
    //you first buy the stock then sell it then do the next transaction starting from the day after selling the stock
    //Find maximum profit that can be obtained by doing atmost k transactions on n number of days?
    int n, k;
    cin >> n >> k;
    int prices[n];
    for (int i = 0; i < n; i++)
        cin >> prices[i];

    cout << stocksII(prices, n, k) << "\n";
    return 0;
}