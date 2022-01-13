#include <bits/stdc++.h>
#define rint(n) scanf("%d", &n);
using namespace std;

// https://www.spoj.com/problems/ARBITRAG/
int main()
{
    int testcase = 0;
    while (++testcase)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        map<string, int> mp;
        for (int i = 0; i < n; ++i)
        {
            string currency;
            cin >> currency;
            mp[currency] = mp.size();
        }
        int m;
        cin >> m;
        double adj[n][n];
        memset(adj, 0.0, sizeof adj);
        for (int i = 0; i < m; ++i)
        {
            string currency1, currency2;
            double exchange_value;
            cin >> currency1 >> exchange_value >> currency2;
            adj[mp[currency1]][mp[currency2]] = exchange_value;
        }
        // Floyd warshall
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    adj[i][j] = max(adj[i][j], adj[i][k] * adj[k][j]);
                }
            }
        }
        bool ok = false;
        for (int i = 0; i < n; ++i)
        {
            if (adj[i][i] > 1.0)
            {
                cout << "Case " << testcase << ": Yes\n";
                ok = true;
                break;
            }
        }

        if (!ok)
        {
            cout << "Case " << testcase << ": No\n";
        }
    }
    return 0;
}