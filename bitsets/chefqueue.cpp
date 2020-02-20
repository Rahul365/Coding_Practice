#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll LIMIT = (1LL << 32LL);
const ll SIZE = (LIMIT / 2LL) + 1LL;
bitset<SIZE> bb;

int main()
{
    // cout << bb.count() << "\n";
    int q;
    cin >> q;
    ll s, a, b;
    cin >> s >> a >> b;

    ll sum = 0L;
    while (q--)
    {
        ll f = s / 2LL;
        if (s & 1LL)
        {
            if (bb[f] == 0)
            {
                bb[f] = 1;
                sum += f;
            }
        }
        else if (bb[f] == 1)
        {
            bb[f] == 0;
            sum -= f;
        }
        s = ((s * a) + b) % LIMIT;
    }
    cout << sum << "\n";
    return 0;
}