#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
// http://codeforces.com/contest/459/problem/D
struct Node
{
    int data;
    Node *left, *right;
    Node(int _data)
    {
        data = _data;
        left = right = NULL;
    }
};

void maxself(int &a, int b)
{
    a = max(a, b);
}

int read(Node *x)
{
    return x ? x->data : 0;
}

void insert(Node *&root, int l, int r, int pos, int val)
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
        insert(root->left, l, mid, pos, val);
    else
        insert(root->right, mid + 1, r, pos, val);

    root->data = read(root->left) + read(root->right);
}

int query(Node *root, int l, int r, int L, int R)
{
    if (!root || l > r || L > R || R < l || r < L)
    {
        return 0;
    }

    if (L <= l && r <= R)
        return root->data;

    int mid = l + ((r - l) >> 1);

    if (R <= mid)
        return query(root->left, l, mid, L, R);
    else if (mid < L)
        return query(root->right, mid + 1, r, L, R);

    return query(root->left, l, mid, L, R) + query(root->right, mid + 1, r, L, R);
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    unordered_map<int, int> freq;
    int l[n];
    int r[n];
    int maxfreq = -1;
    for (int i = 0; i < n; i++)
    {
        l[i] = ++freq[arr[i]];
        maxself(maxfreq, l[i]);
    }
    freq.clear();
    for (int i = n - 1; i >= 0; i--)
    {
        r[i] = ++freq[arr[i]];
        maxself(maxfreq, r[i]);
    }

    maxfreq++;
    ll ans = 0;
    Node *seg = NULL;
    for (int i = 0; i < n; i++)
    {
        insert(seg, 0, maxfreq, r[i] + 1, 1);
    }

    for (int i = 0; i < n; i++)
    {
        insert(seg, 0, maxfreq, r[i] + 1, -1);  //doing this will reduce the occurence of element a[i] from (n-1 to i)
        ans += query(seg, 0, maxfreq, 1, l[i]); //all the elements in the tree will be from range [i+1 .... n-1]
        //counting the number of elements with frequency <= l[i]
    }

    printf("%lld\n", ans);
    return 0;
}