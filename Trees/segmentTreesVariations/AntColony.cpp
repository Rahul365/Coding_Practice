#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pp = pair<ll, ll>;

void mergep(pp *p, int l, int m, int r)
{
    pp *aux = new pp[r - l + 1];
    int idx = 0;
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r)
    {
        if (p[i].first <= p[j].first)
        {
            if (p[i].first > p[j].first)
            {
                aux[idx++] = p[j++];
            }
            else
            {
                aux[idx++] = p[i++];
            }
        }
        else if (p[i].first > p[j].first)
        {

            aux[idx++] = p[j++];
        }
    }

    while (i <= m)
        aux[idx++] = p[i++];
    while (j <= r)
        aux[idx++] = p[j++];
    idx = 0;
    while (l <= r)
    {
        p[l++] = aux[idx++];
    }
    delete (aux);
}

void mergesort(pp *p, int i, int j)
{
    if (i < j)
    {
        int mid = i + ((j - i) >> 1);
        mergesort(p, i, mid);
        mergesort(p, mid + 1, j);
        mergep(p, i, mid, j);
    }
}

void mSort(pp *p, int n)
{
    mergesort(p, 0, n - 1);
}

int find(pp *p, int n, int L, int R, int val)
{
    // cout << "inside find \n";
    int first(-1);
    int last(-1);
    int i = 0;
    int j = n - 1;
    while (i <= j)
    {
        int mid = i + ((j - i) >> 1);
        if (p[mid].first == val)
        {
            if (L <= p[mid].second && p[mid].second <= R)
            {
                first = mid;
                j = mid - 1;
            }
            else if (p[mid].second < L)
            {
                i = mid + 1;
            }
            else
            {
                j = mid - 1;
            }
        }
        else if (p[mid].first < val)
        {
            i = mid + 1;
        }
        else
        {
            j = mid - 1;
        }
    }

    i = 0;
    j = n - 1;
    while (i <= j)
    {

        int mid = i + (j - i) / 2;
        if (p[mid].first == val)
        {
            if (p[mid].second >= L && p[mid].second <= R)
            {
                last = mid;
                i = mid + 1;
            }
            else if (p[mid].second > R)
            {
                j = mid - 1;
            }
            else
                i = mid + 1;
        }
        else if (p[mid].first > val)
        {
            j = mid - 1;
        }
        else
            i = mid + 1;
    }
    if (first == last && first == -1)
        return 0;
    return last - first + 1;
}

ll gcde(ll a, ll b)
{
    //gcd(a,b) = gcd(b,a%b)
    //gcd(a,0) = a
    while (b)
    {
        int n_b = a % b;
        a = b;
        b = n_b;
    }
    return a;
}

struct Node
{
    pair<ll, ll> info;
    Node *left, *right;
    Node()
    {
        left = right = NULL;
    }
    Node(pair<ll, ll> _info)
    {
        info = _info;
        left = right = NULL;
    }
};

pair<ll, ll> getinfo(Node *x)
{
    return x ? x->info : make_pair(0LL, LLONG_MAX);
}

pair<ll, ll> merge(pair<ll, ll> a, pair<ll, ll> b)
{
    return make_pair(gcde(a.first, b.first), min(a.second, b.second));
}

void update(Node *&seg, int l, int r, int pos, ll val)
{
    if (l > r)
        return;
    if (!seg)
        seg = new Node();
    if (l == r)
    {
        seg->info = {val, val};
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update(seg->left, l, mid, pos, val);
    else
        update(seg->right, mid + 1, r, pos, val);
    seg->info = merge(getinfo(seg->left), getinfo(seg->right));
}

pair<ll, ll> query(Node *seg, int l, int r, int L, int R)
{
    if (l > r || r < L || R < l)
    {
        return {0, LLONG_MAX};
    }

    if (L <= l && r <= R)
        return seg->info;

    int mid = l + ((r - l) >> 1);

    if (R <= mid)
        return query(seg->left, l, mid, L, R);
    else if (mid < L)
        return query(seg->right, mid + 1, r, L, R);
    return merge(query(seg->left, l, mid, L, R), query(seg->right, mid + 1, r, L, R));
}

void printpp(pp x)
{
    cout << "(" << x.first << "," << x.second << ")";
}

void testmergesort()
{
    int n = rand() % 101 + 1;
    pp arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = {rand() % 191, i};
        cout << arr[i].first << " ";
    }
    cout << "\n";
    mSort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printpp(arr[i]);
        cout << " ";
    }
    cout << "\n";
}

int main()
{
    //http://codeforces.com/contest/474/problem/F
    //srand(time(NULL));
    // testmergesort();
    //return 0;

    int n;
    cin >> n;
    vector<ll> arr(n);
    pair<ll, ll> parr[n];
    Node *seg = NULL;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        parr[i] = {arr[i], i};
        update(seg, 0, n - 1, i, arr[i]);
    }
    //sort(parr,parr+n);
    mSort(parr, n);
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        pair<ll, ll> info = query(seg, 0, n - 1, l, r);
        int occ = find(parr, n, l, r, info.first);
        cout << (r - l + 1 - occ) << "\n";
    }
    return 0;
}