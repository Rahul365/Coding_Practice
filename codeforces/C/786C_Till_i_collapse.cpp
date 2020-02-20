#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
int n, *arr;

struct Node
{
    int val;
    Node *left, *right;
    Node(int _val)
    {
        val = _val;
        left = right = NULL;
    }
    Node(Node *other)
    {
        val = other->val;
        left = other->left;
        right = other->right;
    }
};

vector<int> push[MAXN];
vector<int> prev_pos(MAXN, 0); //to store the prev position of arr[i]
Node *seg[MAXN];

void updatek(Node *&, int); //to update node value for given pos by +1
void update(Node *&, int, int, int);
int query(Node *, int, int, int);
int findnext(int, int); //to find the start of the next subarray for given k node
int ans[MAXN];          //store the result as ans[k] = minimum number of contiguos subarray groups with atmost k distinct numbers

int getval(Node *x)
{
    return !x ? 0 : x->val;
}

void update(Node *&x, int l, int r, int pos)
{
    if (!x)
        x = new Node(0);
    else
        x = new Node(x);
    if (l == r)
    {
        x->val++;
        return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update(x->left, l, mid, pos);
    else
        update(x->right, mid + 1, r, pos);
    x->val = getval(x->left) + getval(x->right);
}

void updatek(Node *&x, int pos)
{
    update(x, 0, n + 1, pos);
}

int query(Node *x, int l, int r, int limit)
{
    //cout << "Search : " << l << " " << r << " :" << getval(x) << " and key = " << limit << "\n ";
    if (!x)
        return r;
    if (l == r)
        return r;
    int mid = l + (r - l) / 2;
    if (getval(x->left) > limit)
    {
        return query(x->left, l, mid, limit);
    }
    else
    {
        return query(x->right, mid + 1, r, limit - getval(x->left));
    }
}

int findnext(int on, int k)
{
    return query(seg[on], 0, n + 1, on + k - 1);
}

void inorder(Node *rr)
{
    if (!rr)
        return;
    inorder(rr->left);
    cout << rr->val;
    inorder(rr->right);
}

int main()
{
    memset(ans, 0, sizeof ans);
    cin >> n;
    arr = new int[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        push[prev_pos[arr[i]] + 1].push_back(i);
        prev_pos[arr[i]] = i; //update th
    }
    seg[0] = new Node(0);
    for (int k = 1; k <= n; k++)
    {
        seg[k] = new Node(seg[k - 1]);
        for (int pos : push[k])
        {
            updatek(seg[k], pos); //update node at pos in segment tree for k by +1
        }
        // inorder(seg[k]);
        // cout << "\n";
        // cout << "Top : " << getval(seg[k]) << "\n";
    }

    for (int k = 1; k <= n; k++)
    {
        int &res = ans[k - 1];
        int on = 1;
        // cout << "For k : " << k << " => ";
        while (on <= n)
        {
            on = findnext(on, k);
            // cout << on << " ";
            res++;
        }
        // cout << "\n";
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << "\n";
    return 0;
}