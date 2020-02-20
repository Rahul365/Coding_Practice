#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxx = 1e18;
const int maxn = 2e5;

ll seg[4 * maxn];
ll push[4 * maxn];
char w[100];
string s;
int tab[3];

void updaterange(int i, int l, int r, int L, int R, ll val)
{
    if (l > r || r < L || R < l)
        return;
    if (L <= l && r <= R)
    {
        seg[i] += val;
        push[i] += val;
        return;
    }
    int mid = l + (r - l) / 2;
    if (L <= mid)
        updaterange(i + i, l, mid, L, R, val);
    if (mid < R)
        updaterange(i + i + 1, mid + 1, r, L, R, val);
    seg[i] = push[i] + min(seg[i + i], seg[i + i + 1]);
}

void update(int i, int l, int r, int pos, int val)
{
    if (l > r)
        return;
    if (l == r)
    {
        seg[i] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update(i + i, l, mid, pos, val);
    else
        update(i + i + 1, mid + 1, r, pos, val);
    seg[i] = min(seg[i + i], seg[i + i + 1]);
}

ll query(int i, int l, int r, int L, int R)
{
    if (l > r || r < L || R < l)
        return maxx;
    if (L <= l && r <= R)
        return seg[i];

    int mid = l + (r - l) / 2;
    ll ans = maxx;
    if (L <= mid)
        ans = min(ans, query(i + i, l, mid, L, R));
    if (mid < R)
        ans = min(ans, query(i + i + 1, mid + 1, r, L, R));
    return push[i] + ans;
}

int main()
{
    memset(seg, 0, sizeof seg);
    memset(push, 0, sizeof push);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        update(1, 1, n, i, x);
    }

    int q;
    cin >> q;
    getline(cin, s);
    while (q--)
    {
        getline(cin, s);
        stringstream in(s);
        int x, y, z;
        int id = 0;
        while (in >> tab[id])
            ++id;
        x = tab[0];
        ++x;
        y = tab[1];
        ++y;
        if (id == 3)
        {
            //cout << x << " "<< y << " "<<z<<"\n";
            z = tab[2];
            if (x > y)
            {
                updaterange(1, 1, n, 1, y, z);
                updaterange(1, 1, n, x, n, z);
            }
            else
                updaterange(1, 1, n, x, y, z);
        }
        else
        {
            //cout << x <<" "<<y<<"\n";
            ll ans;
            if (x > y)
                ans = min(query(1, 1, n, x, n), query(1, 1, n, 1, y));
            else
                ans = query(1, 1, n, x, y);
            printf("%I64d\n", ans);
        }
    }
    return 0;
}