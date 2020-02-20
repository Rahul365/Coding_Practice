#include <bits/stdc++.h>
using ll = unsigned long long int;
using namespace std;

struct Node
{
    ll data;
    Node *left, *right;
    Node(ll _data)
    {
        data = _data;
        left = right = NULL;
    }
};

ll getdata(Node *root)
{
    return root ? root->data : 0;
}

void update(Node *&root, int l, int r, int pos, ll val)
{
    if (l > r)
        return;
    if (!root)
        root = new Node(0);

    if (l == r)
    {
        root->data += val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
    {
        update(root->left, l, mid, pos, val);
    }
    else
    {
        update(root->right, mid + 1, r, pos, val);
    }
    root->data = getdata(root->left) + getdata(root->right);
}

ll query(Node *root, int l, int r, int L, int R)
{
    if (!root || l > r || r < L || R < l)
        return 0;

    if (L <= l && r <= R)
    {
        return root->data;
    }
    int mid = l + (r - l) / 2;

    if (R <= mid)
    {
        return query(root->left, l, mid, L, R);
    }
    else if (mid < L)
    {
        return query(root->right, mid + 1, r, L, R);
    }
    return query(root->left, l, mid, L, R) + query(root->right, mid + 1, r, L, R);
}

int main()
{
    int n;
    cin >> n;
    vector<pair<ll, int>> a;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        a.push_back({x, i});
    }

    sort(a.begin(), a.end());
    //a[i]<a[i+1]<a[i+2]<...<a[n-2]<a[n-1]
    // i1 <> i2 <> i3 <> ..............<> in-2 <> in-1

    ll ans = 0;
    ll res = 0;
    Node *seg = NULL;  //to store the count of elements a[j] < a[i](say lessthan[i]) , j=>[i+1,n-1] on node of index i
    Node *seg2 = NULL; //to store the sum of lessthan[0...n-1] for range queries
    for (int i = 0; i < n; i++)
    {
        // cout << "Number of elements < " << a[i].first;
        // cout << " = " << (res = query(seg, 0, n - 1, a[i].second + 1, n - 1)) << "\n";
        res = query(seg, 0, n - 1, a[i].second + 1, n - 1);   //number of elements arr[j] < a[i].first such that a[i].second < j
        update(seg, 0, n - 1, a[i].second, 1);                //update a[i].second by 1 i.e. increase the count of a[i].first in it's original index by 1
        update(seg2, 0, n - 1, a[i].second, res);             //update the number of lessthan a[i].first in the range( a[i].secon + 1 ... n-1) with result query from the first segment tree
        ans += query(seg2, 0, n - 1, a[i].second + 1, n - 1); //query the sum of lessthan[j] ... lessthan[n-1] where (a[i].second+1 <= j <= n-1)
    }
    cout << ans << "\n";
    return 0;
}