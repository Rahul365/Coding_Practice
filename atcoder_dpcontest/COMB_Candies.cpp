#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int MAXN = 1e5 + 11, N = 305;
int memo[MAXN];
int K;
//prerequisites : combinatrics knowledge
// and array manupulation tricks
void add_self(int &a, int b)
{
    a += b;
    if (a >= mod)
        a -= mod;
}

void sub_self(int &a, int b)
{
    a -= b;
    if (a < 0)
        a += mod;
}

int distribute(int *c, int pos, int n, int k)
{
    int ways;
    if (k == 0)
        return ways = 1;
    if (pos == n)
        return ways = 0;
    ways = 0;
    for (int cap = 0; cap <= c[pos] && k >= cap; cap++)
    {
        add_self(ways, distribute(c, pos + 1, n, k - cap));
    }
    return ways;
}

int main()
{
    memset(memo, -1, sizeof memo);
    int n, k;
    K = k;
    scanf("%d%d", &n, &k);
    int candies[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &candies[i]);

    vector<int> dp(k + 1, 0);

    dp[0] = 1; //number of ways to distribute 0 candies among n children

    for (int c : candies)
    {
        vector<int> dp2(k + 1, 0);
        for (int used = k; used >= 0; --used)
        {
            int temp = dp[used];
            int L = used + 1;
            int R = used + min(c, k - used);
            if (L <= R)
            {
                add_self(dp2[L], temp);
                if (R + 1 <= k)
                    sub_self(dp2[R + 1], temp);
            }
            /*
                for(int here = 1;here <= min(c , k - used);here++)
                {
                    add_self(dp[used + here],dp[used]);
                }
                */
        }

        for (int i = 0; i <= k; i++)
        {
            if (i)
                add_self(dp2[i], dp2[i - 1]);
            add_self(dp[i], dp2[i]);
        }
    }

    printf("%d\n", dp[k]);

    return 0;
}