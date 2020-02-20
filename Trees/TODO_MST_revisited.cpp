#include <bits/stdc++.h>
#define pp pair<ll, pair<int, int>>
using namespace std;
const int MAXN = 3e5 + 11;
int par[MAXN], _size[MAXN];
using ll = long long;
using ep = pair<int, int>;

vector<pp> edges;

void init(int n)
{
    for (int i = 0; i <= n; i++)
    {
        par[i] = i;
        _size[i] = 1;
    }
}

int root(int x)
{
    while (x != par[x])
    {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

bool wunion(int u, int v)
{
    int rx = root(u);
    int ry = root(v);
    if (rx == ry)
        return false;
    if (_size[rx] < _size[ry])
        swap(rx, ry);
    _size[rx] += _size[ry];
    par[ry] = rx;
    return true;
}

set<pp> mwe[2]; //store the edges used/not used  in sorted order according to their weights
set<pair<int, int>> used, unused;
map<pair<int, int>, ll> etow;

void addtomwe(ep edge, ll w, int id)
{
    if (mwe[id].find({etow[edge], edge}) != mwe[id].end())
    {
        mwe[id].erase({etow[edge], edge});
    }
    mwe[id].insert({w, edge});
}

void addtoused(ep edge, ll w)
{
    //add to max weight eights of mst
    addtomwe(edge, w, 0);
    used.insert(edge);
    etow[edge] = w;
}

void addtounused(ep edge, ll w)
{
    addtomwe(edge, w, 1);
    unused.insert(edge);
    etow[edge] = w;
}

void removefrommwe(ep edge, ll w, int id)
{
    mwe[id].erase({w, edge});
}

void removefromused(ep edge)
{
    removefrommwe(edge, etow[edge], 0);
    used.erase(edge);
    etow.erase(edge);
}

void removefromunused(ep edge)
{
    removefrommwe(edge, etow[edge], 1);
    unused.erase(edge);
    etow.erase(edge);
}

ll kruskal()
{
    init(edges.size() + 1);
    ll mst = 0;
    sort(edges.begin(), edges.end());
    for (auto edge : edges)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        if (wunion(u, v))
        {
            addtoused({u, v}, edge.first);
            mst += edge.first;
        }
        else
        {
            addtounused({u, v}, edge.first);
        }
    }
    return mst;
}

void print(ep p)
{
    cout << p.first << "," << p.second << "\n";
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        ll w;
        int u, v;
        scanf("%d%d%lld", &u, &v, &w);
        if (u > v)
            swap(u, v);
        edges.push_back({w, {u, v}});
    }

    ll mst = kruskal();
    int a, b, c, d;
    ll wt;
    bool first;
    ll ans = 0;
    while (m--)
    {
        scanf("%d%d%d%d%lld", &a, &b, &c, &d, &wt);
        a += (ans % 100);
        b += (ans % 100);
        c += (ans % 100);
        d += (ans % 100);
        wt += (ans % 100);
        if (a > b)
            swap(a, b);
        if (c > d)
            swap(c, d);
        ep R = {a, b}; //edge to remove
        ep A = {c, d}; //edge to add
        /*same edge is being added or removed*/
        if (a == c && b == d)
        {
            if (used.find(R) != used.end())
            {
                /*edge belong to used set of edges*/
                mst -= etow[R];
                /*remove from the used set */
                removefromused(R);
                /*add it to unused set*/
                addtounused(R, wt);
                /*pick minimum weighted edge from the unused set of edges*/
                auto it = mwe[1].begin();
                ep emin = (*it).second;
                ll wmin = (*it).first;
                removefromunused(emin); /*remove the minimum weighted edge from the unused set of edges and add it to mst*/
                addtoused(emin, wmin);
                mst += wmin;
            }
            else if (unused.find(R) != unused.end())
            {
                removefromunused(R);
                addtoused(R, wt);
                mst += wt;
                /*pick the maximum weighted edge from the set of used edges
                and add it to the set of unused edges*/
                auto it = mwe[0].rbegin();
                ll wmax = (*it).first;
                ep emax = (*it).second;
                mst -= wmax;
                removefromused(emax);
                addtounused(emax, wmax);
            }
        }
        else
        {
            /*when two edges to remove and add are not the same*/
            if (used.find(R) != used.end())
            {
                mst -= etow[R];
                removefromused(R);
            }
            else if (unused.find(R) != unused.end())
            {
                removefromunused(R);
            }

            if (used.find(A) != used.end())
            {
                mst -= etow[A];
                removefromused(A);
                addtounused(A, wt);
            }
            else if (unused.find(A) != unused.end())
            {
                removefromunused(A);
                mst += wt;
                addtoused(A, wt);
            }

            int _edge_count = used.size();
            if (_edge_count > n - 1)
            {
                while (_edge_count > n - 1)
                {
                    auto it = mwe[0].rbegin();
                    mst -= (*it).first;
                    addtounused((*it).second, (*it).first);
                    removefromused((*it).second);
                    _edge_count = used.size();
                }
            }
            else if (_edge_count < n - 1)
            {
                while (_edge_count < n - 1)
                {
                    auto it = mwe[1].begin();
                    mst += (*it).first;
                    addtoused((*it).second, (*it).first);
                    removefromunused((*it).second);
                    _edge_count = used.size();
                }
            }
        }

        printf("%lld\n", mst);
        ans = mst;
    }

    return 0;
}