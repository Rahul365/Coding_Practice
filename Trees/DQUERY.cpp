#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
const int N = 3e5 + 10;
const int Q = 200000 + 10;
int tree[N];
int p[MAXN];
pair<int, pair<int, int>> pr[N];
int ans[N];

void update(int idx, int val)
{
    while (idx < N)
    {
        tree[idx] += val;
        idx += (idx & (-idx));
    }
}

int read(int idx)
{
    int sum = 0;
    while (idx > 0)
    {
        sum += tree[idx];
        idx -= (idx & (-idx));
    }
    return sum;
}

int main()
{
    int n;
    cin >> n;
    int arr[n + 1];
    arr[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    memset(tree, 0, sizeof(tree));
    memset(ans, 0, sizeof(ans));
    memset(p, -1, sizeof(p));

    int q;
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> pr[i].second.first >> pr[i].first;
        pr[i].second.second = i;
    }

    sort(pr + 1, pr + q + 1);

    int x = 1;
    for (int i = 1; i <= n; i++)
    {
        if (p[arr[i]] != -1)
            update(p[arr[i]], -1);
        p[arr[i]] = i;
        update(i, 1);
        while (x <= q && pr[x].first == i)
        {
            ans[pr[x].second.second] = read(pr[x].first) - read(pr[x].second.first - 1);
            ++x;
        }
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
    return 0;
}