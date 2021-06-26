// https://codeforces.com/problemset/problem/932/F
// Li Chao tree application
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll inf = 1e18;
const int N = 2e5 + 1;
const int C = 1e5 + 5;
int n;
vector<int> *g;
vector<int> a(N), b(N);
vector<ll> dp(N);

struct Line
{
    ll x;
    ll y;
    Line(ll x = 0, ll y = inf) : x(x), y(y) {}
    ll operator()(ll a)
    {
        return (a * x) + y;
    }
};

struct Node
{
    Line line;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(Line _line = Line()) : line(_line), left(nullptr), right(nullptr) {}
};

void add_line(Line in, int l, int r, Node *&node)
{
    if (node == nullptr)
    {
        node = new Node(in);
        return;
    }
    int m = l + (r - l) / 2;
    bool left = in(l) < node->line(l);
    bool mid = in(m + 1) < node->line(m + 1);

    if (mid)
    {
        swap(node->line, in);
    }

    if (l == r)
        return;
    if (left != mid)
    {
        add_line(in, l, m, node->left);
    }
    else
    {
        add_line(in, m + 1, r, node->right);
    }
}

ll getMin(int l, int r, ll x, Node *&node)
{
    if (node == nullptr)
        return inf;
    if (l == r)
        return node->line(x);
    int mid = l + (r - l) / 2;
    if (x <= mid)
        return min(node->line(x), getMin(l, mid, x, node->left));
    else
        return min(node->line(x), getMin(mid + 1, r, x, node->right));
}

void merge(Node *&a, Node *b)
{
    if (b->line.y != inf || b->line.x != 0)
        add_line(b->line, -C, C, a);
    if (b->left)
        merge(a, b->left);
    if (b->right)
        merge(a, b->right);
}

void deleteChild(Node *&root)
{
    if (root)
    {
        deleteChild(root->left);
        deleteChild(root->right);
        delete root;
    }
}

pair<int, Node *> dfs(int u, int p)
{
    int sizeOftree = 0;
    Node *par = new Node();
    for (int v : g[u])
    {
        if (v == p)
            continue;
        auto [subtreeSize, child] = dfs(v, u);
        if (subtreeSize > sizeOftree)
        {
            swap(par, child);
        }
        merge(par, child);
        deleteChild(child);
        sizeOftree += subtreeSize;
    }
    dp[u] = sizeOftree ? getMin(-C, C, a[u], par) : 0;
    add_line(Line(b[u], dp[u]), -C, C, par);
    return {sizeOftree + 1, par};
}

void init()
{
    fill(dp.begin(), dp.end(), inf);
}

int main()
{
    init();
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }

    g = new vector<int>[n + 1];
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    dfs(1, 1);
    for (int i = 1; i <= n; ++i)
    {
        printf("%lld ", dp[i]);
    }

    return 0;
}