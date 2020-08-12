#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
#define pii pair<ll, pair<ll, int>>
class Solution
{
public:
    int nthSuperUglyNumber(int n, vector<int> &primes)
    {
        const int k = primes.size();
        priority_queue<pii, vector<pii>, greater<pii>> q;
        vector<ll> ugly(n + 2);
        ugly[0] = 1;
        for (int i = 0; i < k; ++i)
            q.push({(ll)primes[i], {(ll)primes[i], 0}});

        for (int index = 1; index < n + 1; ++index)
        {
            ugly[index] = q.top().first;
            // cout << ugly[index] << " ";
            while (!q.empty() && q.top().first == ugly[index])
            {
                auto p = q.top();
                q.pop();
                p.second.second++;
                // cout << ugly[p.second.second] << " " <<p.second.first<<"\n";
                p.first = ugly[p.second.second] * p.second.first;
                q.push(p);
            }
        }
        // cout << ugly[n-1] <<"\n";
        return ugly[n - 1];
    }
};