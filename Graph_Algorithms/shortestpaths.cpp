#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, int>
using namespace std;
const int N = 1e5;
const int NN = 100;
const ll MAX = 1e5; //max bound constraint

/*Floyd Warshall Algorithm -> O(n^3)*/
ll adj[NN][NN];
ll floydWarshall(int source, int destination, int V)
{
    ll dist[NN][NN];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dist[i][j] = (i == j) ? 0 : MAX;
        }
    }
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist[source][destination];
}

const int E = 1e5;
const ll INF = 2e9;
vector<int> g[E]; //g[edge] = {u,v,w}
vector<ll> dist(N, INF);
/*O((Verices-1)*Edges) == O(Edges^2)
In case Edges = Vertices*(Vertices - 1)/2 ~= Vertices^2
Then Complexity is O(Vertices^3)
 Used for negative cycle detection 
 For after n-1 iterations of this algorithm 
 do one more iterations if any change in the distances happen then there is a negative cycle in the graph
*/
ll bellmanford(int source, int destination, int vertices)
{
    fill(dist.begin(), dist.end(), INF); //set the distance of all nodes to infinity
    dist[source] = 0;
    //loop 0 to vertices-1
    for (int i = 0; i < vertices - 1; ++i)
    {
        int j = 0;
        //for each edge check if distance of next vertex is  > than dist[from] + weight(u,v)
        while (g[j].size() != 0)
        {
            int u = g[j][0];
            int v = g[j][1];
            ll w = g[j][2];
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
            ++j; //traverse all the edges for n-1 times
        }
    }
    return dist[destination];
}

vector<bool> vis(N, false); //to mark the visited vertices
vector<pii> gg[N];          //graph representation  gg[from] = {weight,to}
/*
    O(V^2) without min priority queue
    O(V + E log V) with min priority queue
*/
ll dijkstra(int source, int destination)
{

    fill(dist.begin(), dist.end(), INF);
    fill(vis.begin(), vis.end(), false);

    priority_queue<pii, vector<pii>, greater<pii>> q; //min-priority queue
    //pair(ll,int) with minimum ll value will always be at the top
    q.push({0, source});
    dist[source] = 0;

    while (!q.empty())
    {
        int u = q.top().second; //get the vertex with smallest distance from the source
        q.pop();

        if (vis[u])
            continue;
        vis[u] = true;

        for (pii p : gg[u])
        {
            int v = p.second;
            ll w = p.first;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }

    return dist[destination];
}
