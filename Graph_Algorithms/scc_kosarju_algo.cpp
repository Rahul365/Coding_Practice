#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class SCCKosaraju
{
    stack<int> stk;
    bool *vis;
    vector<int> *grev;
    void dfs(int src, vector<int> *g)
    {
        vis[src] = true;
        for (int v : g[src])
        {
            if (vis[v])
                continue;
            dfs(v, g);
        }
        stk.push(src);
    }

public:
    /*  Function to find the number of strongly connected components
    *   using Kosaraju's algorithm
    *   V: number of vertices
    *   adj[]: array of vectors to represent graph
    */
    int kosaraju(int V, vector<int> adj[])
    {
        stk = std::move(stack<int>());
        vis = new bool[V];
        grev = new vector<int>[V];
        for (int u = 0; u < V; ++u)
        {
            for (int v : adj[u])
            {
                grev[v].emplace_back(u);
            }
        }
        for (int i = 0; i < V; ++i)
            vis[i] = false;
        for (int i = 0; i < V; ++i)
        {
            if (!vis[i])
                dfs(i, adj);
        }
        for (int i = 0; i < V; ++i)
            vis[i] = false;
        int ans = 0;
        while (!stk.empty())
        {
            int src = stk.top();
            stk.pop();
            if (vis[src])
                continue;
            ++ans;
            dfs(src, grev);
        }
        return ans;
    }
};

int main()
{
    return 0;
}