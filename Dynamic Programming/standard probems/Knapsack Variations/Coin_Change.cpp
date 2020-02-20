#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6;

int makechangerec(int *coins, int n, int nc)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;

    /**
     * if the number of coins left are zero and change is still greater than 0
     * then change is not possible using current way of selecting coins
    */
    if (nc == 0 && n > 0)
        return 0;

    return makechangerec(coins, n - coins[nc - 1], nc) + makechangerec(coins, n, nc - 1);
}

int makechangesdp(int *coins, int sum, int nc)
{
    int dp[nc][sum + 1];

    for (int i = 0; i < nc; i++)
    {
        dp[i][0] = 1;
    }

    for (int k = 1; k <= sum; k++)
    {
        for (int i = 0; i < nc; i++)
        {
            dp[i][k] = 0;
            if (k >= coins[i])
            {
                dp[i][k] += dp[i][k - coins[i]];
            }
            if (i >= 1)
            {
                dp[i][k] += dp[i - 1][k];
            }
        }
    }

    return dp[nc - 1][sum];
}

int makechangedpOnspace(int *coins, int sum, int m)
{
    int table[sum + 1];
    memset(table, 0, sizeof(table));
    table[0] = 1;

    for (int i = 0; i < m; i++)
    { //number of coins
        for (int j = coins[i]; j <= sum; j++)
        { //start from coin with value coin[i] to sum value given
            table[j] += table[j - coins[i]];
        }
    }
    return table[sum]; //number of ways to obtains sum value change from the given number of cells
}

int memo[1000][1000];
bool vis[1000][1000];
int ways(int *coins, int sum, int m)
{
    if (m == 0)
    {
        return sum == 0;
    }
    if (sum < 0)
        return 0;

    int &ans = memo[m][sum];
    if (vis[m][sum])
    {
        return ans;
    }
    vis[m][sum] = true;
    // int times = 0;
    /* Slow state transistions*/
    // while(times * coins[m-1] <= sum){
    //     ans += ways(coins,sum-times*coins[m-1],m-1);
    //     times++;
    // }
    ans = ways(coins, sum - coins[m - 1], m) + ways(coins, sum, m - 1);
    return ans;
}

int main()
{
    int sum = 150; //amount for which we need the change
    int nc = 10;   //number of coins
    int coins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << makechangerec(coins, sum, nc) << "\n";
    cout << makechangesdp(coins, sum, nc) << "\n";
    cout << makechangedpOnspace(coins, sum, nc) << "\n";
    cout << ways(coins, sum, nc) << "\n";
    return 0;
}