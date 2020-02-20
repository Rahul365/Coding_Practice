#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int MAXN = 2e5 + 11;
vector<int> g[MAXN];
vector<int> color;
int n, m, a, b;
/*
    Given a graph with n vertices(labeled from 1 to  n) and m bidirectional edges.
    Given two vertices labels a and b.
    Find the number of pairs of vertices (x,y) that
    path from x to y must pass through the both vertices a and b in any order.
    It is gurranted that you can reach any vertex from any other vertex i.e. graph has no disconnected components.
    
*/
void dfs(int u, int c)
{
    if (color[u])
        return;
    color[u] = c;
    for (int v : g[u])
    {
        dfs(v, c);
    }
}

vector<int> groups(int f)
{
    color = vector<int>(n + 1, 0);
    color[f] = -1; //remove vertex f
    int c = 0;     //component id
    for (int i = 1; i <= n; i++)
        if (i != f && !color[i])
            dfs(i, ++c);

    return color;
}

ll solve()
{
    ll ans = ((ll)(n - 2) * ((n - 2) - 1) / 2);
    map<int, int> pp;
    vector<pair<int, int>> p(n - 2); //-2 because we are removing a and b

    //remove vertex a
    vector<int> gr = groups(a);
    int index = 0;
    for (int i = 1; i <= n; i++)
        if (i != a && i != b)
            p[index++].first = gr[i]; //store the component id of vertex i when vertex a is removed
    //remove vertex b
    gr = groups(b);
    index = 0;
    for (int i = 1; i <= n; i++)
        if (i != a && i != b)
            p[index++].second = gr[i]; //store the component id of vertex i when vertex b is removed

    map<int, int> p1;

    for (int i = 0; i < n - 2; i++)
    {
        p1[p[i].first]++; //number of vertices in the component p[i].first when vertex a is removed
    }

    for (pair<int, int> vc : p1)
        ans -= ((ll)vc.second * (vc.second - 1) / 2);

    p1.clear();

    for (int i = 0; i < n - 2; i++)
    {
        p1[p[i].second]++; //number of vertices in the component p[i].second when vertex b is removed
    }

    for (pair<int, int> vc : p1)
        ans -= ((ll)vc.second * (vc.second - 1) / 2);

    map<pair<int, int>, int> p2;
    for (int i = 0; i < n - 2; i++)
        p2[p[i]]++;
    for (pair<pair<int, int>, int> vc : p2)
        ans += ((ll)vc.second * (vc.second - 1) / 2);

    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> a >> b;

        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << solve() << "\n";
        for (int i = 1; i <= n; i++)
            g[i].clear();
    }
    return 0;
}