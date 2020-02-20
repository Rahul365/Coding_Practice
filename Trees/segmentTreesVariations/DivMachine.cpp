#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int MAX = 1e6 + 1;
const int MAXN = 1e5 + 1;
// https://www.codechef.com/problems/DIVMAC
int seg[4 * MAXN];
int a[MAXN];
int lprime[MAX];

void insert(int i, int l, int r, int pos, int val)
{
    if (l > r)
        return;
    if (r == pos && l == r)
    {
        seg[i] = val;
        return;
    }
    int mid = l + ((r - l) >> 1);
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (pos <= mid)
        insert(left, l, mid, pos, val);
    else
        insert(right, mid + 1, r, pos, val);

    seg[i] = max(lprime[seg[left]], lprime[seg[right]]);
}

void update(int i, int l, int r, int L, int R)
{
    if (l > r || r < L || R < l)
        return;
    if (L <= l && r <= R && l != r && lprime[seg[i]] == 1) //maximum least prime of all the number in the range l to r is 1 : no need to update this range
        return;

    if (L <= l && r <= R && l == r)
    {
        // cout<<"udpating at " << l << " from "  << seg[i] << " to " <<(seg[i]/lprime[seg[i]])<<"\n";
        seg[i] = seg[i] / lprime[seg[i]];
        return;
    }
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int mid = l + ((r - l) >> 1);

    update(left, l, mid, L, R);
    update(right, mid + 1, r, L, R);

    seg[i] = max(lprime[seg[left]], lprime[seg[right]]);
}

int query(int i, int l, int r, int L, int R)
{
    if (l > r || R < l || r < L)
        return 1;

    if (L <= l && r <= R)
        return lprime[seg[i]];

    int mid = l + ((r - l) >> 1);
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (R <= mid)
        return query(left, l, mid, L, R);
    else if (mid < L)
        return query(right, mid + 1, r, L, R);
    return max(query(left, l, mid, L, R), query(right, mid + 1, r, L, R));
}

void segseive()
{
    lprime[0] = lprime[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        lprime[i] = i;
    }
    for (int i = 2; i * i < MAX; i++)
    {
        if (lprime[i] == i)
        {
            for (int j = i * i; j < MAX; j += i)
                if (lprime[j] == j)
                    lprime[j] = i;
        }
    }
}

int main()
{
    segseive();

    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(seg, 0, sizeof seg);
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            insert(0, 0, n - 1, i, a[i]);
        }

        int ty, l, r;
        while (m--)
        {
            scanf("%d%d%d", &ty, &l, &r);
            if (ty == 0) //update query
            {
                update(0, 0, n - 1, l - 1, r - 1);
            }
            else
            { //get query
                printf("%d ", query(0, 0, n - 1, l - 1, r - 1));
            }
        }
        printf("\n");
    }
    return 0;
}