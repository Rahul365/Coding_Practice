#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 11;
vector<int> seg(MAXN, 0); //segment tree node

void update(int i, int l, int r, int pos, int val, int depth)
{
    if (pos == l && l == r)
    {
        seg[i] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (pos <= mid)
    {
        update(left, l, mid, pos, val, depth - 1);
    }
    else
    {
        update(right, mid + 1, r, pos, val, depth - 1);
    }

    if (depth & 1)
    {
        seg[i] = seg[left] | seg[right];
    }
    else
    {
        seg[i] = seg[left] ^ seg[right];
        /* code */
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    int N = 1 << n;
    int SIZE = pow(2, ceil(log2(N + 1))) - 1;
    seg.resize(SIZE);

    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        update(0, 0, N - 1, i, x, n);
    }

    while (m--)
    {
        int p, q;
        cin >> p >> q;
        update(0, 0, N - 1, p - 1, q, n);
        cout << seg[0] << "\n";
    }
    return 0;
}