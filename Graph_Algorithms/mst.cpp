/*Minimum spanning trees*/

#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, pair<int, int>> // (w -> (u-v)) for kruskal algo
#define piii pair<ll, int>           //  g[u] = (w,v)  for prims algo
using namespace std;

const int N = 1e5;
int parent[N];
int sz[N];

template<typename T>
class dsu{
    vector<T> parent;
    vector<T> size;
    T n;
    public:;
    dsu(T _n){
        n = _n;
        parent = vector<T>(n+1);
        size = vector<T>(n+1);
        for(int i = 0;i<=n;++i)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    T root(T u){
        while(parent[u]!=u){
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    }
    
    bool wunion(T u, T v){
        T ru = root(u);
        T rv = root(v);
        if(ru == rv) return false;
        if(size[ru]< size[rv])
            swap(ru,rv);
        parent[rv] = ru;
        size[ru] += size[rv];
        return true;
    }
    
    T numberOfDisconnectedComponents(){
        T ans =0;
        for(int i = 1;i<=n;++i)
            ans += (parent[i] == i);
        return ans;
    }
};

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