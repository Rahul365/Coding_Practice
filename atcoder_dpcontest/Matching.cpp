#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

void add_self(int &a, int b)
{
    a = a + b;
    if (a >= mod)
        a -= mod;
}

int getcount(int num)
{
    int ans = 0;
    while (num)
    {
        ans += (1 & num);
        num >>= 1;
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    int p[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> p[i][j];
        }
    }

    vector<int> dp(1 << n); //bitmask dp (2^n)
    //dp[i]

    dp[0] = 1;

    for (int masks = 0; masks < (1 << n) - 1; ++masks)
    {
        int a = getcount(masks);
        for (int b = 0; b < n; b++)
        {
            if (p[a][b] && !(masks & (1 << b)))
            {
                int m2 = masks ^ (1 << b);
                add_self(dp[m2], dp[masks]);
            }
        }
    }

    cout << dp[(1 << n) - 1] << "\n";
    return 0;
}