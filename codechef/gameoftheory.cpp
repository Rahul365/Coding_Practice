#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#define boost                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define ll long long int
using namespace std;
const int MAXN = 1e5 + 11;
const int LG = 20;
vector<int> g[MAXN];
ll a[MAXN];
ll b[MAXN];
int n;

int timer = -1;
int in[MAXN];
int out[MAXN];
//u and v are on the same path
//if (in[u] < in[v] && out[u] > out[v]) pr (in[u] > in[v] && out[u] < out[v])
void dfsinout(int u, int par)
{
    in[u] = ++timer;
    for (int v : g[u])
    {
        if (v == par)
            continue;
        dfsinout(v, u);
    }
    out[u] = ++timer;
}

int main()
{
    boost;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &b[i]);
    }
    int u, v;
    for (int i = 1; i < n; i++)
    {
        // cin>>u>>v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll R = 0;
    dfsinout(1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if ((in[i] <= in[j] && out[i] >= out[j]) || (in[i] > in[j] && out[j] > out[i]))
                R += min(max(a[i], a[j]), max(b[i], b[j]));
        }
    }

    cout << R << "\n";
    return 0;
}