#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minJumps(vector<int> &arr)
    {
        /*BFS solution*/
        const int n = arr.size();

        map<int, vector<int>> graph;

        for (int i = 0; i < n; ++i)
        {
            graph[arr[i]].emplace_back(i);
        }

        vector<int> curr;           // store the nodes of the current level
        vector<bool> vis(n, false); // mark the visited nodes with true value

        curr.emplace_back(0); // push the start node

        int step = 0;

        while (!curr.empty())
        {
            vector<int> next; // to store the nodes of the next level
            for (int node : curr)
            {
                if (node == n - 1)
                {
                    return step;
                }

                for (int child : graph[arr[node]])
                {
                    if (child != node && !vis[child])
                    {
                        vis[child] = true;
                        next.emplace_back(child);
                    }
                }
                for (int child : {node - 1, node + 1})
                {
                    if (child >= 0 && child < n && !vis[child])
                    {
                        vis[child] = true;
                        next.emplace_back(child);
                    }
                }

                graph[arr[node]].clear(); // clear the list of child nodes for the current node to avoid redundant visits
            }
            curr = next;
            ++step;
        }

        return -1; // dummy return statement
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &v : arr)
    {
        cin >> v;
    }
    /*
    input:
    10
    100 -23 -23 404 100 23 23 23 3 404
    output:
    3
    */
    cout << Solution().minJumps(arr) << '\n';
    return 0;
}