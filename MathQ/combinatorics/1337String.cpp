#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
template <typename T>
vector<T> pf(T n)
{
    vector<T> ans;
    for (T i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                ans.emplace_back(i);
                n /= i;
            }
        }
    }
    if (n > 0)
    {
        ans.emplace_back(n);
    }
    return ans;
}

char ch[] = {'1', '3', '3', '7'};
using ll = long long int;
ll count(ll n)
{
    return n * (n + 1) / 2;
}

void solve(ll n)
{
    /*
        n = 43
        1 2 3  4  5  6  7  8  9 10
        1 3 6 10 15 21 28 36 45 55
        x = 9 where count(x-1)=36 < 43
        rem = 43-36 = 7
        1(33)(7..upto rem times)(33......upto x-2 times)7
    */
    ll x = 1;
    while (count(x - 1) <= n)
    {
        ++x;
    }
    x -= 1;
    ll rem = n - count(x - 1LL);
    string ans = "1" + string(2, '3') + string(rem, '7') + string(x - 2, '3') + "7";
    cout << ans << "\n";
}
// https://codeforces.com/problemset/problem/1202/D
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        solve(n);
    }
    return 0;
}