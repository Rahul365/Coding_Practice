#include <bits/stdc++.h>
using namespace std;
template <typename T>
priority_queue<T, vector<T>, greater<T>> min_heap()
{
    return std::move(priority_queue<T, vector<T>, greater<T>>());
}

std::pair<int, int> operator+(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return std::make_pair<int, int>(a.first + b.first, a.second + b.second);
}

class Solution
{
    const int INF = 1e9 + 7;
    vector<pair<int, int>> dir;

public:
    Solution()
    {
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                if (abs(i) == abs(j))
                    continue;
                dir.push_back({i, j});
            }
        }
    }
    int cutOffTree(vector<vector<int>> &forest)
    {
        const int m = forest.size();
        if (!m)
            return 0;
        const int n = forest.back().size();
        auto pq = min_heap<pair<int, pair<int, int>>>(); //this will give us the next target cell
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
            {
                if (forest[i][j] > 1)
                    pq.push({forest[i][j], {i, j}});
            }

        int steps = 0;
        auto src = std::make_pair<int, int>(0, 0);

        while (!pq.empty())
        {
            pair<int, int> curr_point = pq.top().second;
            pq.pop();
            int prev = steps;
            // std::cout << "curr "<<src.first << " " << src.second <<" \n";

            //reach the next greater tree cell
            queue<pair<int, pair<int, int>>> q;
            q.push({0, src});
            vector<vector<bool>> vis(m, vector<bool>(n, false));
            vis[src.first][src.second] = true;
            while (!q.empty())
            {
                src = q.front().second;
                int dist = q.front().first;
                if (src == curr_point)
                {
                    steps += dist;
                    break;
                }
                q.pop();
                for (auto &d : dir)
                {
                    auto next = src + d;
                    if (!(next.first >= 0 && next.second >= 0 && next.first < m && next.second < n) || forest[next.first][next.second] == 0 || vis[next.first][next.second])
                    {
                        continue;
                    }
                    vis[next.first][next.second] = true;
                    q.push({dist + 1, next});
                }
            }

            if (q.empty())
                return -1;
            //after reaching that cell cut off the tree
            forest[src.first][src.second] = 1;
        }
        return steps;
    }
};

int main()
{
    return 0;
}