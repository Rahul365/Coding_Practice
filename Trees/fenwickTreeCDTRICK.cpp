#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e4 + 1000;
int bit[MAXN];

int N;

void update(int pos, int val)
{
    int index = pos + 1;
    while (index < N)
    {
        bit[index] += val;
        index += (index & (-index));
    }
}

int getsum(int pos)
{
    int sum = 0;
    int index = pos + 1;
    while (index > 0)
    {
        sum += bit[index];
        index -= (index & (-index));
    }
    return sum;
}

void buildtree(int n)
{
    N = n + 1;
    memset(bit, 0, sizeof(bit));
    for (int i = 1; i < N; i++)
        update(i - 1, 1); //each node will contain the number of free cells so far
}

vector<int> arrangecards(int n)
{
    int freecells = n;
    int num_to_place = 0;
    vector<int> ans(n + 2, -1);
    int left = 1;
    while (freecells)
    {
        ++num_to_place;
        left = (left + num_to_place) % freecells;
        left = !left ? freecells : left;

        int s = 1;
        int e = n;
        //search for the position of free cell
        while (s <= e)
        {
            int mid = s + (e - s) / 2;
            if (getsum(mid - 1) >= left)
            {
                e = mid - 1;
            }
            else
            {
                s = mid + 1;
            }
        }
        ans[s] = num_to_place;
        update(s - 1, -1);
        --freecells;
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        buildtree(n);
        vector<int> ans = arrangecards(n);
        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << "\n";
    }
    return 0;
}