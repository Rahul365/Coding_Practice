#include <cstdio>
#include <iostream>
#define readint(x) scanf("%d", &x)
using namespace std;
const int MAXN = 3e5 + 1;
int *seg;
int *ans;

//http://codeforces.com/contest/356/problem/A

void update(int i, int l, int r, int L, int R, int val)
{
    if (l > r || L > R || R < l || r < L)
        return;

    if (seg[i] != 0)
        return;
    if (l == r)
    {
        if (ans[l] == 0 && l == val)
            return;
        seg[i] = ans[l] = (ans[l] == 0 ? val + 1 : ans[l]);
        return;
    }

    int mid = l + (r - l) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (R <= mid)
        update(left, l, mid, L, R, val);
    else if (mid < L)
        update(right, mid + 1, r, L, R, val);
    else
    {
        update(right, mid + 1, r, L, R, val);
        update(left, l, mid, L, R, val);
    }
    seg[i] = min(seg[left], seg[right]);
}

int main()
{
    int n, m;
    readint(n);
    readint(m);

    ans = new int[n];
    for (int i = 0; i < n; i++)
        ans[i] = 0;
    seg = new int[4 * n];
    for (int i = 0; i < 4 * n; i++)
        seg[i] = 0;
    int l, r, winner;

    while (m--)
    {
        readint(l);
        readint(r);
        readint(winner);
        update(0, 0, n - 1, l - 1, r - 1, winner - 1);
        /*
           for(int i=l-1;i<=r-1;i++)
           {
               if(ans[i] == 0 && i == winner-1)continue;
               ans[i] = (ans[i]==0?winner:ans[i]);    
           }
       */
    }
    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}