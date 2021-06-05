#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 11;
const int LG = 20;
const int INF = 1e9 + 7;
using ll = long long int;
vector<pair<int, int>> g[maxn];
vector<int> par;
int n;
//A node u is the centroid node of the tree iff max(subtreesize[childrens of u]) >= subtree[u]/2
struct CDMP
{
    vector<bool> dead;
    int root;
    vector<int> par;
    vector<int> cdtree[maxn];
    int oneCentroid(int u)
    {
        static int subtree[maxn];
        function<void(int, int)> dfs = [&](int u, int p)
        {
            subtree[u] = 1;
            for (pair<int, int> v : g[u])
            {
                if (v.first == p || dead[v.first])
                    continue;
                dfs(v.first, u);
                subtree[u] += subtree[v.first];
            }
        };
        dfs(u, -1);
        int N = subtree[u];
        function<int(int, int)> findCentroid = [&](int u, int p)
        {
            for (pair<int, int> v : g[u])
            {
                if (v.first == p || dead[v.first])
                    continue;
                if (2 * subtree[v.first] > N)
                    return findCentroid(v.first, u);
            }
            return u;
        };

        int res = findCentroid(u, -1);
        return res;
    }

    void traverse(int u, int p)
    {
        par[u] = p;
        // cerr << u  << " ";
        for (int v : cdtree[u])
        {
            if (v != p)
                traverse(v, u);
        }
    }

    vector<int> &decomposeTree()
    {
        dead = vector<bool>(maxn, false);
        par = vector<int>(maxn, -1);
        function<int(int)> rec = [&](int u)
        {
            int cu = oneCentroid(u);
            dead[cu] = true;
            for (pair<int, int> v : g[cu])
            {
                if (!dead[v.first])
                {
                    int cv = rec(v.first);
                    cdtree[cu].push_back(cv);
                    cdtree[cv].push_back(cu);
                }
            }
            return cu;
        };
        root = rec(1);
        traverse(root, -1);
        // cerr <<"\n";
        return par;
    }
} cdmp;

struct LCA
{
    int par[maxn][20];
    int dist[maxn];
    int level[maxn];
    void dfs(int u, int p)
    {
        level[u] = 1 + level[p];
        par[u][0] = p;
        for (pair<int, int> v : g[u])
            if (v.first != p)
            {
                dist[v.first] = v.second + dist[u];
                dfs(v.first, u);
            }
    }

    int distance(int u, int v)
    {
        return dist[u] + dist[v] - 2 * dist[findlca(u, v)];
    }

    int findlca(int u, int v)
    {
        if (level[u] < level[v])
            swap(u, v);
        int lg = 0;
        while ((1 << lg) <= level[u])
            ++lg;
        --lg;
        for (int i = lg; i >= 0; --i)
            if (level[u] - (1 << i) >= level[v])
                u = par[u][i];

        if (u == v)
            return u;
        for (int i = lg; i >= 0; --i)
            if (par[u][i] != -1 && par[u][i] != par[v][i])
                u = par[u][i], v = par[v][i];

        return par[u][0];
    }

    void build()
    {
        level[1] = 0;
        for (int i = 1; i < maxn; ++i)
            par[i][0] = -1;
        dfs(1, 1);
        for (int i = 1; i < LG; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (par[j][i - 1] != -1)
                {
                    par[j][i] = par[par[j][i - 1]][i - 1];
                }
            }
        }
    }
} lca;

vector<int> color(maxn);
vector<pair<ll, ll>> maxdist(maxn, {-INF, -INF});
//A node can be black or white
//if it is white , then 0 can be considered as distance of node to itself
//if it is black , then only the maximum distance of this node to it's white children will be added

/*
        1
       /\
      2  3
     /\
    4 5

    if 2 is turned black
    then for node 1 max distance = dist(1,whitenodeOnright) + dist(1,whitenodeOnleft)
    dist(1,whitenodeOnleft) = (if(node 2 have any white children in its subtree)) dist(1,2) + dist(2,maxdistantwhitechildren);


*/

void maxself(ll &a, ll b)
{
    a = max(a, b);
}

vector<pair<int, ll>> data[maxn];
ll curr_max;
void init(int u, int p = -1)
{
    // cerr << u << " " <<color[u] <<"\n";
    ll curr = color[u] ? 0 : -INF;
    ll &ret1 = maxdist[u].first = curr;
    ll &ret2 = maxdist[u].second = curr;
    for (int v : cdmp.cdtree[u])
    {
        if (v == p)
            continue;
        init(v, u); /*max distance node from the subtree rooted from node v in the centroid Decomposed Tree*/
        ll d = max(maxdist[v].first, maxdist[v].second);
        if (!color[v] && d == -INF)
            continue;
        ll dd = lca.distance(u, v);
        maxself(dd, dd + d);
        if (ret1 < dd)
        {
            ret2 = ret1;
            ret1 = dd;
        }
        else if (ret2 < dd)
        {
            ret2 = dd;
        }
    }
    if (ret1 != -INF && ret2 != -INF)
        curr = max(curr, ret1 + ret2);
    if (ret1 != -INF && color[u])
        curr = max(curr, ret1);
    if (ret2 != -INF && color[u])
        curr = max(curr, ret2);
    curr_max = max(curr_max, curr);
}

void update(int u)
{
    color[u] = 1 - color[u];
    curr_max = -INF;
    init(cdmp.root);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    fill(color.begin(), color.end(), 1);
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v, c;
        cin >> u >> v >> c;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }
    lca.build();
    par = cdmp.decomposeTree();
    init(cdmp.root);
    // cerr <<"MAX DISTANCE : "<<curr_max<<"\n";
    int q;
    cin >> q;
    while (q--)
    {
        char ch;
        cin >> ch;
        if (ch == 'C')
        {
            int u;
            cin >> u;
            update(u);
        }
        else if (ch == 'A')
        {
            if (curr_max == -INF)
            {
                cout << "They have disappeared.\n";
                return 0;
            }
            else
            {
                cout << curr_max << "\n";
            }
        }
    }
    // # build lca
    //process queries
    return 0;
}