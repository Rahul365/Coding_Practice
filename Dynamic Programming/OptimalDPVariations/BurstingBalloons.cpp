#include <bits/stdc++.h>
using namespace std;
/**
 * Given n number of balloons b[],
 * All are painted with color of value b[i].
 * When you burst a balloon , you get coins = b[left] * b[i] * b[right],
 * where left and right are adjacent left and right balloons of i.
 * Only after bursting balloon i ,then left and right becomes adjacent.
 * Find the maximum number of coins collected by bursting all the balloons.
 * b[-1] = b[n] = 1;(imaginary balloons)
 * e.g 
 * n = 4;
 * b[] = {3 , 1 , 5 ,8}
 * {3,1,5,8} (burst 1 = (3 * 1 * 5))
 * {3,5,8}   (burst 5 = (3 * 5 * 8))
 * {3,8}     (burst 3 = (1 * 3 * 8)) 
 * {8}       (burst 8 = (1 * 8 * 1))
 * Total coins        = 15 + 120 + 24 + 8 = 167
*/

/**
 * Idea of solution is to start from the last
 * i.e start from imagining that ith balloon is the last balloon you burst
 * //coins you get from ith balloon = (1 * b[i] * 1)
 * then when you select 2nd last balloon to burst
 * you have ith balloon bursted lastly available as either left or right of balloons you are about to burst
 * dp[L][R] => maxcoins collected by bursting balloons in range[L...R] from last
 * Therefore
 *  dp[L][R] = (b[L-1] * b[i]  * b[R+1]) + dp[i+1][R] + dp[L][i-1];
 * we'll take care of boundary checks in the implementation below.
*/

void maxself(int &a, int b)
{
    a = max(a, b);
}

void test(int n)
{ //test length gaps
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i; j < n; j++)
        {
            cout << i << " " << j << " , ";
        }
        cout << "\n";
    }
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    if (!n)
        return 0;
    vector<vector<int>> dp(n, vector<int>(n));

    for (int L = n - 1; L >= 0; L--)
    {
        for (int R = L; R < n; R++)
        {
            for (int i = L; i <= R; i++)
            {
                dp[L][R] = max(dp[L][R], (L == 0 ? 1 : nums[L - 1]) * nums[i] * (R == n - 1 ? 1 : nums[R + 1]) + (L <= i - 1 ? dp[L][i - 1] : 0) + (R >= i + 1 ? dp[i + 1][R] : 0));
            }
        }
    }
    return dp[0][n - 1];
}

int maxcoins(vector<int> &b)
{
    int n = b.size();
    if (!n)
        return 0;
    vector<vector<int>> dp(n, vector<int>(n));
    for (int len = 1; len <= n; len++)
    {
        for (int L = 0; L <= n - len; L++)
        {
            int R = L + len - 1;
            for (int toburst = L; toburst <= R; toburst++)
            {
                //bursting ith last balloon 'toburst'
                //such that L-1 and R + 1 are adjacent to it
                int left = L == 0 ? 1 : b[L - 1];
                int right = R == n - 1 ? 1 : b[R + 1];
                //cout << left << "  " << b[toburst] << " " << right << "\n";
                maxself(dp[L][R],
                        b[toburst] * left * right + (R >= toburst + 1 ? dp[toburst + 1][R] : 0) + (L <= toburst - 1 ? dp[L][toburst - 1] : 0));
            }
        }
    }
    return dp[0][n - 1];
}

int main()
{
    int n;
    cin >> n;
    vector<int> balloons(n);
    for (int i = 0; i < n; i++)
    {
        cin >> balloons[i];
    }
    cout << maxcoins(balloons) << "\n";
    return 0;
}