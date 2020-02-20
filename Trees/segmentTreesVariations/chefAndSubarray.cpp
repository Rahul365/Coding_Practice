// https://www.codechef.com/problems/CHEFSUBA
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
int *seg;
int n, k, p;
string Q;
int *arr; //binary array of 0 and 1
//prequisites used:
//1)Rotation trick
//2)Deque or (Segment Tree (Max range query))

void update(int i, int l, int r, int pos, int val)
{
    if (l > r)
        return;
    if (l == r)
    {
        seg[i] = val;
        return;
    }
    int mid = l + ((r - l) >> 1);
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (pos <= mid)
    {
        update(left, l, mid, pos, val);
    }
    else
    {
        update(right, mid + 1, r, pos, val);
    }
    seg[i] = max(seg[left], seg[right]);
}

int query(int i, int l, int r, int L, int R)
{
    if (l > r || L > R || r < L || R < l)
    {
        return 0;
    }
    if (L <= l && r <= R)
        return seg[i];
    int mid = l + ((r - l) >> 1);
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (R <= mid)
        return query(left, l, mid, L, R);
    else if (L > mid)
    {
        return query(right, mid + 1, r, L, R);
    }
    return max(query(left, l, mid, L, R), query(right, mid + 1, r, L, R));
}

void solveusingsegmenttree()
{
    //let's precompute the sum of elements for each <=k size frame
    int h = ceil(log2(n));
    int N = 2 * pow(2, h + 1) - 1;
    seg = new int[N];

    int sum[2 * n];
    sum[0] = arr[0];
    for (int i = 1; i < 2 * n; i++)
    {
        sum[i] = sum[i - 1] + arr[i] - (i >= k ? arr[i - k] : 0);
        update(0, 0, 2 * n - 1, i, sum[i]);
    }

    int start_index = 0;
    for (char ch : Q)
    {
        if (ch == '?')
        {
            cout << query(0, 0, 2 * n - 1, start_index + k - 1, start_index + n - 1) << "\n";
        }
        else if (ch == '!')
        { //tracking the next starting position after right rotation by one element
            if (--start_index < 0)
                start_index += n;
        }
    }
}

void solveusingdeque()
{
    int sum[2 * n];
    sum[0] = arr[0];
    for (int i = 1; i < 2 * n; i++)
    {
        sum[i] = sum[i - 1] + arr[i] - (i >= k ? arr[i - k] : 0);
    }

    deque<int> q; //to store the maximum frame of 1's i.e maximum number of 1's on frame for each start position

    for (int i = 0; i < n; i++)
    {
        while (!q.empty() && sum[q.back()] <= sum[i])
            q.pop_back();
        q.push_back(i);
    }

    int maxframe[n]; //for each index as start position
    int start_pos = 0;
    for (int i = n; i <= 2 * n; i++)
    {
        maxframe[start_pos++] = sum[q.front()];
        if (i == 2 * n)
            break;
        while (!q.empty() && q.front() < start_pos + k - 1)
        {
            q.pop_front();
        }
        while (!q.empty() && sum[q.back()] <= sum[i])
        {
            q.pop_back();
        }
        q.push_back(i);
    }

    start_pos = 0;
    for (char q : Q)
    {
        if (q == '!')
        {
            if (--start_pos < 0)
            {
                start_pos += n;
            }
        }
        else if (q == '?')
        {
            cout << maxframe[start_pos] << "\n";
        }
    }
}

int main()
{
    cin >> n >> k >> p;
    arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> Q;

    if (k >= n)
    {
        //when frame size is greater then or equal to n
        //then no matter how many times the array is rotated right by 1 position
        //result will be the total number of 1's in the array
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += arr[i];
        for (char ch : Q)
        {
            if (ch == '?')
            {
                cout << ans << "\n";
            }
        }
    }
    else
    {
        //two ways we can solve this problem
        //1) Using segment trees O(n*logn)
        //2) Using Deque(sliding window mechanism) O(n)

        //Let's first  apply the rotation trick
        // here
        int *tmp = arr;
        arr = new int[2 * n]; //double the size of the array
        //now append the array to itself
        //i.e arr[] = {1,0,0,1,1}
        // Append the arr[] copy at the end of the original array
        // updated arr[] = {1,0,0,1,1,1,0,0,1,1,1};
        for (int i = 0; i < n; i++)
            arr[i] = arr[i + n] = tmp[i];
        //With this we have every possible rotation of the array
        //e.g. For an array of 5 elements arr[]={arr[0],arr[1],arr[2],...,arr[4]}
        // Initially starting element of the array is at the index = 0
        //  After rotating right it by 1 length, we have
        //  arr[] = {arr[4], arr[0] , arr[1] ,arr[2], arr[3]}
        // So now element at 4th index becomes the first element of the rotated array
        // But thanks to the trick we used, we don't have to rotate the array
        // but just decide on the next starting position after rotation which is 4 in our case
        // In new arr[2*n] , elements in range [4,4+n-1] represent the rotated array after 1 right rotation
        //Now since we have to maximize the total number of 1's in a frame we can greedily pick each frame of size k

        //O(n * logn)
        solveusingsegmenttree();
        //O(n)
        solveusingdeque();
    }
    return 0;
}