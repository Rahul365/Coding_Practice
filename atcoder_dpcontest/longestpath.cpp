#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 3;
vector<int> g[MAXN];
vector<int> indeg(MAXN, 0);
vector<int> depth(MAXN, -1);

int ans = 0;
int dfs(int u, int d)
{
    if (depth[u] != -1)
        return depth[u];
    for (int v : g[u])
    {
        depth[u] = max(depth[u], 1 + dfs(v, d + 1));
    }
    return depth[u];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int root = 0;
    int x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        indeg[y]++;
        g[x].push_back(y);
    }

    for (int i = 1; i <= n; i++)
        if (!indeg[i])
        {
            indeg[i]++;
            g[root].push_back(i);
        }

    // ans = dfs(0, 0);
    queue<pair<int, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        ans = max(ans, d);
        for (int v : g[u])
        {
            if (!(--indeg[v]))
            {
                q.push({v, 1 + d});
            }
        }
    }
    printf("%d\n", ans - 1);
    return 0;
}