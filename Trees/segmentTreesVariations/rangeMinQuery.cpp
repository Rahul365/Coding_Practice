#include <cstdio>
#include <climits>
#include <cstring>
#include <vector>
#define readint(x) scanf("%d", &x)
#define printint(x) printf("%d", x)
#define println printf("\n")
using namespace std;
const int MAXN = 1e5 + 1;
int seg[4 * MAXN];
int segbits[4 * MAXN];
int mask = (1 << 30) - 1; //mask of 31 bits

int query(int i, int l, int r, int L, int R)
{
    if (l > r || r < L || R < l)
        return INT_MAX;
    if (L <= l && r <= R)
        return seg[i];
    int mid = l + (r - l) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (R <= mid)
        return query(left, l, mid, L, R);
    else if (L > mid)
        return query(right, mid + 1, r, L, R);

    return min(query(left, l, mid, L, R), query(right, mid + 1, r, L, R));
}

void insert(int i, int l, int r, int pos, int val)
{
    if (l > r)
        return;
    if (l == r)
    {
        seg[i] = segbits[i] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (pos <= mid)
        insert(left, l, mid, pos, val);
    else
        insert(right, mid + 1, r, pos, val);

    seg[i] = min(seg[left], seg[right]);
    segbits[i] = segbits[left] | segbits[right];
}

void updaterange(int i, int l, int r, int L, int R, int x)
{
    if (l > r || r < L || R < l)
        return;
    if (!(segbits[i] & (mask ^ x))) //if true -> this condition here determines whether
    //there exists a number A[i] in the range L to R for which it's corresponding bits are oppositely set in
    //x.
    //eg. Let mask = 1111 and x = 0100(4)
    // and segbits[i] = (0110) 6
    // (mask ^ x) = 1011 (unset bits in x)
    // segbits[i] & (mask ^ x)  = 0110 & ( 1011 ) =0010 (yes there exits some integer A[i] in  range [L:R]
    // for which x has opppositely set bit in it
    //)
    {
        return; //no number within this node's interval for which num  has 1 bit and node has 0 bit or vice versa
        //no need to update in this interval
    }

    if (l == r)
    {
        seg[i] = segbits[i] = seg[i] & x;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (R <= mid)
        updaterange(left, l, mid, L, R, x);
    else if (mid < L)
        updaterange(right, mid + 1, r, L, R, x);
    else
    {
        updaterange(left, l, mid, L, R, x);
        updaterange(right, mid + 1, r, L, R, x);
    }
    seg[i] = min(seg[left], seg[right]);
    segbits[i] = segbits[left] | segbits[right];
}

int main()
{
    memset(seg, 0, sizeof seg);
    memset(segbits, 0, sizeof segbits);
    int n, q;
    readint(n);
    readint(q);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        readint(arr[i]);
        insert(0, 0, n - 1, i, arr[i]);
    }
    int t, l, r;
    int val;
    while (q--)
    {
        readint(t); //read type of query
        readint(l); //read left end of query
        readint(r); //read right end of query
        if (t == 0) //type 1 query
        {
            //print min in rannge [L : R]
            printint(query(0, 0, n - 1, l - 1, r - 1));
            println;
        }
        else
        {
            readint(val);
            //update range update [L : R]
            updaterange(0, 0, n - 1, l - 1, r - 1, val);
        }
    }
    return 0;
}