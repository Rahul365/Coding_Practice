#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 1e9 + 7;
const int MAXN = 1e5 + 11;

vector<int> g[MAXN];

void add_self(int &a, int b)
{
    a += b;
    if (a >= mod)
        a -= mod;
}

int mult(int a, int b)
{
    return (ll)a * b % mod;
}

pair<int, int> dfs(int u, int p)
{
    int allwhite = 1; //this means vertex u can be painted black
    int anyblack = 0; //this means atleast one vertex is black
    for (int v : g[u])
    {
        if (v == p)
            continue;
        pair<int, int> res = dfs(v, u);
        //number of ways to paint the subtree rooted from v if v is white
        anyblack = (mult(allwhite, res.first) + mult(anyblack, res.first + res.second)) % mod;
        //
        allwhite = mult(allwhite, res.second);
    }
    return {allwhite, (allwhite + anyblack) % mod};
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    pair<int, int> p = dfs(1, 1);
    int ans = (p.first + p.second) % mod;
    printf("%d\n", ans);
    return 0;
}