/**
 *  Given a tree with n nodes and n-1 edges.
 *  Find the sum of distance of tree for each node as root.
 *  Sum(i) => sum of distances of every node from node i
 *  where 0 <= i < n 
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 11;
vector<int> g[MAXN];

int n;
vector<int> subtreesum(MAXN, 0); //to store the subtree sum rooted from node x
vector<int> countN(MAXN, 1);     //1 + number of nodes in the subtree rooted from node x

//Algorithm
//Let the current root node be 0
//
//1)For root = 0, do postorder dfs traversal and compute:
//
// countN[node] += countN[child];
//  subtreesum[node] += subtreesum[child] + countN[child];
//
//2) do preorder dfs traversal
// and compute the sum of distances for each node using the parent data
// subtreesum[child] = subtreesum[parent]-countN[child] + N - countN[child];
// dfsrec(child,parent);

void dfs1(int u, int p)
{
    for (int v : g[u])
    {
        if (v == p)
            continue;
        dfs1(v, u);
        countN[u] += countN[v];
        subtreesum[u] += subtreesum[v] + countN[v];
    }
}

void dfs2(int u, int p)
{
    for (int v : g[u])
    {
        if (v == p)
            continue;
        subtreesum[v] = subtreesum[u] + n - 2 * countN[v];
        //here subtree[child] = subtree[parent] - count[child + (n-count[child]);
        // subtree[parent]-count[child] => (Sum of distances of subtree from parent + Sum of distances of subtree from child)
        // (n-count[child]) => number of nodes in subtree rooted from parent (unlinked from it's child)
        dfs2(v, u);
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    for (int i = 0; i < n; i++)
        cout << subtreesum[i] << " ";
    cout << "\n";
    return 0;
}