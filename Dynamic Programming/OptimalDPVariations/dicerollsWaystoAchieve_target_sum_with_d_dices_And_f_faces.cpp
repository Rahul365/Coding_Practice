#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

void addself(int &a, int b)
{
    a += b;
    if (a >= mod)
    {
        a -= mod;
    }
}
/**
 * returns the number of ways to achieve target sum by rolling d dices 
 * with face values from [1 to f]
*/
int ways(int d, int f, int target)
{
    if (!d)             //if 0 dice to roll
        return !target; //return 1 only if target sum to achieve is 0
    vector<vector<int>> dp(d + 1, vector<int>(target + 1));
    dp[0][0] = 1;
    for (int roll = 0; roll < d; roll++)
    {
        for (int face = 1; face <= f; face++)
        {
            for (int sum = 0; sum + face <= target; sum++)
            {
                addself(dp[roll + 1][sum + face], dp[roll][sum]);
            }
        }
    }

    return dp[d][target];
}

int main()
{
    int d;      //number of dices to roll
    int f;      //faces in a dice from 1,2,3,....,f
    int target; //target sum to achieve by rolling d dices
    cin >> d >> f >> target;
    cout << ways(d, f, target) << "\n";
    return 0;
}