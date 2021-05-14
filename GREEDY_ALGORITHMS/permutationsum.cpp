#include <bits/stdc++.h>
using namespace std;
const int maxn = 501;
const int sum = 1e5 + 3e4;
// https://codeforces.com/contest/1512/problem/E
bool rec(int x, int use, int sum, vector<int> &ans)
{

    if (!sum)
    {
        return !use;
    }
    if (!use)
    {
        return false;
    }

    if (!x)
        return false;
    if (rec(x - 1, use, sum, ans))
    {
        return true;
    }
    else if (sum - x >= 0 && rec(x - 1, use - 1, sum - x, ans))
    {
        ans.emplace_back(x);
        return true;
    }
    return false;
}

int getlow(int k)
{
    return k * (k + 1) / 2;
}

int gethigh(int k, int n)
{
    return k * (n + n - k + 1) / 2;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, l, r, s;
        cin >> n >> l >> r >> s;
        //s-> sum
        //r-l+1 -> exact number of elements to sum s and numbers should be in range[1,n]
        //n-> number of elements [1,n]
        int total = (n * (n + 1)) >> 1; //total sum possible
        // problem
        // using r-l+1 number of elements with possible values [1,n], generate sum == s;
        // print those elements that sum upto s.
        int m = r - l + 1;
        int low = getlow(m);//min_possible sum obtainable
        int high = gethigh(m, n);//max_possible sum obtainable
        // cerr << low << " " << high <<"\n";
        //if s doesn't falls in the limits, then answer is not possible
        if (s < low || s > high)
        {
            cout << "-1\n";
            continue;
        }
        //otherwise, greedily try to form an answer
        vector<int> ans;
        for (int i = n; i >= 1; --i)
        {
            auto H = gethigh(m, i);//using i as the limit , max possible sum obtainable using m numbers
            auto L = getlow(m - 1);//min possible sum obtainable using m-1 numbers
            if (s - i >= 0 && m > 0 && s <= H && s - i >= L)
            {
                s -= i;
                --m;
                ans.emplace_back(i);
            }
        }
        if (s != 0)
        {
            cout << "-1\n";
            continue;
        }
        vector<int> arr(n + 1);
        iota(arr.begin(), arr.end(), 0);
        //for(int i = 0;i<=n;++i) cerr << arr[i] <<" \n"[i==n];
        for (int v : ans)
        {
            swap(arr[v], arr.back());
            arr.pop_back();
        }
        swap(arr[0], arr.back());
        arr.pop_back();
        for (int cnt = 1, i = 0, j = 0; cnt <= n; ++cnt)
        {
            if (l <= cnt && cnt <= r)
            {
                cout << ans[i++] << " ";
            }
            else
            {
                cout << arr[j++] << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}