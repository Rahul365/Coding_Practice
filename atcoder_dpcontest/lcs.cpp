#include <bits/stdc++.h>
using namespace std;
string ans;
const int MAXN = 3002;

void lcs(string s, string t, int n, int m, string res)
{
    if (n == 0 || m == 0)
    {
        if (ans.length() < res.length())
        {
            ans = res;
        }
        return;
    }
    if (s[n - 1] == t[m - 1])
        lcs(s, t, n - 1, m - 1, string(1, s[n - 1]) + res);
    else
    {
        lcs(s, t, n - 1, m, res);
        lcs(s, t, n, m - 1, res);
    }
}

string lcs(const string &s, const string &t)
{
    int n = s.length();
    int m = t.length();
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[j - 1][i]);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << dp[i][j] << " ";
        cout << "\n";
    }
    string ans = "";
    int i = n;
    int j = m;
    int len = dp[n][m];
    while (i > 0 && j > 0 && len)
    {
        while (dp[i][j] == dp[i - 1][j - 1]) //go diagonally up
            --i, --j;
        while (dp[i][j] == dp[i - 1][j]) //go vertically up
            --i;
        while (dp[i][j] == dp[i][j - 1]) //go horizontally left
            --j;
        if (s[i - 1] == t[j - 1])
        {
            ans = s[i - 1] + ans;
            --i, --j;
            --len;
        }
    }
    return ans;
}

int main()
{
    string s;
    string t;
    cin >> s >> t;

    cout << lcs(s, t) << "\n";
    return 0;
}