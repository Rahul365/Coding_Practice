#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 11;
using ll = long long int;
vector<int> bit(MAXN, 0);
// http://codeforces.com/contest/459/problem/D
void update(int pos, int val)
{
    int id = pos + 1;
    while (id < bit.size())
    {
        bit[id] += val;
        id += (id & -id);
    }
}

int read(int id)
{
    int sum = 0;
    while (id > 0)
    {
        sum += bit[id];
        id -= (id & -id);
    }
    return sum;
}

int sum(int l, int r)
{
    return read(r) - read(l);
}

//1 <= a[i] <= 1e9
//1 <= n <= 1e6
int main()
{
    int n;
    scanf("%d", &n);
    bit.resize(n + 1);
    int arr[n];

    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int l[n], r[n];
    for (int i = 0; i < n; i++)
    {
        l[i] = ++freq[arr[i]]; //frequency of number arr[i] from 0 to ith index
    }
    freq.clear();
    for (int i = n - 1; i >= 0; i--)
    {
        r[i] = ++freq[arr[i]]; //frequency of number arr[i] from n-1 to ith index
        update(r[i], 1);       //update the value of frequency r[i] +1 in the binary indexed tree
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        update(r[i], -1); //update r[i] => r[i]+(-1)
        //to count the number of elements with frequency less than l[i] in the tree
        ans += sum(1, l[i]);
    }
    printf("%lld\n", ans);
    return 0;
}