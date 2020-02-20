#include <bits/stdc++.h>
const int mod = 1e9 + 7;
using namespace std;

int paths(bool **mat, int r, int c)
{
    //can go only right and down
    int dp[r][c];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i < r; i++)
    {
        if (!mat[i][0])
            break;
        dp[i][0] = dp[i - 1][0];
    }

    for (int j = 1; j < c; j++)
    {
        if (!mat[0][j])
            break;
        dp[0][j] = dp[0][j - 1];
    }

    for (int i = 1; i < r; i++)
    {
        for (int j = 1; j < c; j++)
        {
            if (!mat[i][j])
                continue;

            if (mat[i - 1][j])
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (mat[i][j - 1])
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
    }
    return dp[r - 1][c - 1];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    bool **mat = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        mat[i] = new bool[m];
        for (int j = 0; j < m; j++)
        {
            char ch;
            cin >> ch;
            mat[i][j] = (ch == '.' ? true : false); //1 for path and 1 for no path
        }
    }

    printf("%d\n", paths(mat, n, m));
    return 0;
}