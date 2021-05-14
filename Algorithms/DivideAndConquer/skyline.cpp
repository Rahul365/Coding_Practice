#include <bits/stdc++.h>
using namespace std;
class Solution
{
    using skyline = vector<vector<int>>;
    vector<vector<int>> merge(skyline &left, skyline &right)
    {
        const int n = left.size();
        const int m = right.size();
        vector<vector<int>> ans;
        int i = 0;
        int j = 0;
        int hleft = 0;
        int hright = 0;
        // cout <<"here " << n << " " << m <<"\n";
        while (i < n && j < m)
        {
            if (left[i][0] < right[j][0])
            {
                hleft = left[i][1];
                if (ans.size() && ans.back()[1] == max(hright, hleft))
                {
                    ++i;
                    continue;
                }
                ans.emplace_back(vector<int>({left[i][0], max(hright, hleft)}));
                ++i;
            }
            else if (left[i][0] > right[j][0])
            {
                hright = right[j][1];
                if (ans.size() && ans.back()[1] == max(hright, hleft))
                {
                    ++j;
                    continue;
                }
                ans.emplace_back(vector<int>({right[j][0], max(hright, hleft)}));
                ++j;
            }
            else
            {
                hleft = left[i][1];
                hright = right[j][1];
                if (ans.size() && ans.back()[1] == max(hright, hleft))
                {
                    ++i;
                    ++j;
                    continue;
                }
                ans.emplace_back(vector<int>({left[i][0], max(hright, hleft)}));
                ++i;
                ++j;
            }
        }
        while (i < n)
            ans.emplace_back(left[i++]);
        while (j < m)
            ans.emplace_back(right[j++]);
        return ans;
    }
    vector<vector<int>> buildSkyline(vector<vector<int>> &strips, int l, int r)
    {
        vector<vector<int>> res;
        if (l > r)
            return res;
        if (l == r)
        {
            res.push_back(vector<int>({strips[l][0], strips[l][2]}));
            res.push_back(vector<int>({strips[l][1], 0}));
            return res;
        }
        int m = l + (r - l) / 2;
        auto leftskyline = buildSkyline(strips, l, m);
        auto rightskyline = buildSkyline(strips, m + 1, r);
        return merge(leftskyline, rightskyline);
    }

public:
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
    {
        const int n = buildings.size();
        return buildSkyline(buildings, 0, n - 1);
    }
};

int main()
{
    vector<vector<int>> buildings(
        {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
    for (auto strip : (new Solution())->getSkyline(buildings))
    {
        std::cout << strip[0] << " " << strip[1] << "\n";
    }
    return 0;
}