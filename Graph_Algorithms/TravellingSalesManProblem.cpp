#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 20;
const ll inf = 1e12L + 1;
ll graph[maxn][maxn];
ll dp[maxn][(1 << maxn)];

ll tspSolve(int source, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < (1 << n); ++j)
        {
            dp[i][j] = inf;
        }
    }
    dp[source][(1 << source)] = 0;
    for (int j = 0; j < n; ++j)
    {
        if (source != j)
        {
            dp[j][(1 << source) | (1 << j)] = min(dp[j][(1 << source) | (1 << j)], graph[source][j]);
        }
    }

    for (int r = 3; r <= n; ++r)
    {
        vector<int> arr(n, 0);
        for (int i = n - r; i < n; ++i)
            arr[i] = 1;
        do
        {
            ll mask = 0;
            for (int i = 0; i < n; ++i)
            {
                if (arr[i])
                    mask |= (1 << (n - i - 1));
            }
            //cout << mask <<"\n";
            if (!(mask & (1 << source)))
                continue;
            for (int next = 0; next < n; ++next)
            {
                if (mask & (1 << next) && next != source)
                {
                    //trying to reach i via some j node here
                    ll minDist = inf;
                    int id = -1;
                    for (int curr = 0; curr < n; ++curr)
                    {
                        //visit next(!=curr) from curr
                        //curr->next
                        if (curr != source && curr != next && graph[curr][next] && (mask & (1 << curr)) && dp[curr][mask ^ (1 << next)] != inf)
                        {
                            //cout << dp[curr][mask^(1<<next)] + graph[curr][next] <<"\n";
                            if (minDist > dp[curr][mask ^ (1 << next)] + graph[curr][next])
                            {
                                minDist = min(minDist, dp[curr][mask ^ (1 << next)] + graph[curr][next]);
                            }
                        }
                    }
                    if (minDist != inf)
                    {
                        dp[next][mask] = minDist;
                    }
                }
            }
        } while (next_permutation(arr.begin(), arr.end()));
    }

    ll ans = inf;
    for (int e = 0; e < n; ++e)
    {
        if (e != source && dp[e][(1 << n) - 1] != inf)
        {
            ans = min(ans, dp[e][(1 << n) - 1] + graph[e][source]);
        }
    }
    return ans;
}

vector<int> findOptimalTour(int source, int n)
{
    int last_index = source;
    //record the tour here
    vector<int> tour(n + 1, 0);
    //set the initial state
    int state = (1 << n) - 1;
    for (int i = n - 1; i > 0; --i)
    {
        int index = -1;
        for (int j = 0; j < n; ++j)
        {
            if (j != source && state & (1 << j))
            {
                index = index == -1 ? j : index;
                //compare dist(index->last_index) and dist(j->last_index);
                int prevDist = dp[index][state] + graph[index][last_index];
                int newDist = dp[j][state] + graph[j][last_index];
                if (prevDist > newDist)
                {
                    index = j;
                }
            }
        }
        tour[i] = index;
        //remove the current node from the state
        state = state ^ (1 << index);
        last_index = index;
    }
    tour[0] = tour[n] = source;
    return tour;
}

int main()
{
    int n, source;
    cin >> n >> source;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> graph[i][j];
        }
    }
    cout << tspSolve(source, n) << "\n";
    cout << "Optimal tour : ";
    for (int node : findOptimalTour(source, n))
    {
        cout << node << " ";
    }
    cout << "\n";
    return 0;
}