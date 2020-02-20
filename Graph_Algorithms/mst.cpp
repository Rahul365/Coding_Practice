/*Minimum spanning trees*/

#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, pair<int, int>> // (w -> (u-v)) for kruskal algo
#define piii pair<ll, int>           //  g[u] = (w,v)  for prims algo
using namespace std;

const int N = 1e5;
int parent[N];
int sz[N];

void init()
{
    for (int i = 0; i < N; i++)
    {
        sz[i] = 1;
        parent[i] = i;
    }
}

int root(int x)
{
    while (x != parent[x])
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool wunion(int x, int y)
{
    int rx = root(x);
    int ry = root(y);
    if (rx == ry)
        return false;
    if (sz[rx] < sz[ry])
    {
        swap(rx, ry);
    }
    parent[ry] = rx;
    sz[rx] += sz[ry];
    return true;
}

vector<pii> edges;
/*O(E * logV)*/
ll kruskalMST()
{
    init();                           //initialize disjoint set union data structure
    sort(edges.begin(), edges.end()); //sort the edges in increasing order their weight
    ll minimumcost = 0;
    ll cost;
    for (pii p : edges)
    {
        int x = p.second.first;
        int y = p.second.second;
        cost = p.first;
        if (wunion(x, y))
        {
            minimumcost += cost;
        }
    }

    return minimumcost;
}

vector<piii> g[N];
vector<bool> vis(N, false);
/*O((V+E) * logV)*/
ll primsMST(int s)
{
    fill(vis.begin(), vis.end(), false);

    priority_queue<piii, vector<piii>, greater<piii>> q;
    q.push({0, s});

    ll mincost = 0;

    while (!q.empty())
    {
        piii p = q.top();
        q.pop();
        int u = p.second;
        ll cost = p.first;

        if (vis[u])
            continue;
        vis[u] = true;
        mincost += cost;

        for (piii pp : g[u])
        {
            if (vis[pp.second])
                continue;
            q.push(pp);
        }
    }
    return mincost;
}

int main()
{
    return 0;
}