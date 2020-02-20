#include <bits/stdc++.h>
using namespace std;

int callcount = 0;
//O(2^n)
bool isinterleave(char *a, char *b, char *c)
{

    if (!(*a || *b || *c)) //if all strings are empty then C is interleave of A and B
        return true;
    if (!*c) //if C is empty before A and B then c is not interleave of A and B
        return false;
    ++callcount;
    return (*a == *c && isinterleave(a + 1, b, c + 1)) || (*b == *c && isinterleave(a, b + 1, c + 1));
}
/**
 * Memoization with 3d storage 
*/
bool isinterleave(char *a, char *b, char *c, int i, int j, int k, vector<vector<vector<int>>> &memo)
{

    if (!(*a || *b || *c)) //all strings are empty
        return true;
    if (!*c)
        return false;
    int &ans = memo[i][j][k];
    if (ans != -1)
        return ans == 1;
    ++callcount;
    ans = (*a == *c && isinterleave(a + 1, b, c + 1, i + 1, j, k + 1, memo)) || (*b == *c && isinterleave(a, b + 1, c + 1, i, j + 1, k + 1, memo));
    return ans;
}

bool isinterleave(string a, string b, string c)
{
    ++callcount;
    int n = a.length();
    int m = b.length();
    int t = c.length();
    if (t != n + m)
        return false;
    bool dp[n + 1][m + 1];
    memset(dp, false, sizeof dp);

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == j && i == 0)
            {
                dp[i][j] = true; //both empty strings can make an empty interleaving string
            }
            else if (i == 0) //  string a is empty
            {
                if (b[j - 1] == c[j - 1])
                    dp[i][j] = dp[i][j - 1];
            }
            else if (j == 0) //string b is empty
            {
                if (a[i - 1] == c[i - 1])
                    dp[i][j] = dp[i - 1][j];
            }
            else if (a[i - 1] == c[i + j - 1] && b[j - 1] != c[i + j - 1]) //string a match c but b != c
            {
                dp[i][j] = dp[i - 1][j];
            }
            else if (a[i - 1] != c[i + j - 1] && b[j - 1] == c[i + j - 1]) //string b match c but a != c
            {
                dp[i][j] = dp[i][j - 1];
            }
            else if (a[i - 1] == b[j - 1] && a[i - 1] == c[i + j - 1]) //string a match c && b match c
            {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    return dp[n][m];
}

bool checkinterleave(string a, string b, string c)
{
    int n = a.length();
    int m = b.length();
    int t = c.length();
    if (t != n + m)
        return false;

    //declare a 3d table intialize with -1 as value
    vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(m + 1, vector<int>(t + 1, -1)));
    return isinterleave(&a[0], &b[0], &c[0], 0, 0, 0, memo);
}

int main()
{
    string A = "aabcc";
    string B = "dbbca";
    string C = "aadbbcbcac";
    callcount = 0;
    cout << checkinterleave(A, B, C) << " " << callcount << "\n"; //recursion with memoization
    callcount = 0;
    cout << isinterleave(A, B, C) << " " << callcount << "\n"; // linear table
    callcount = 0;
    cout << isinterleave(&A[0], &B[0], &C[0]) << " " << callcount << "\n"; //recursion
    return 0;
}