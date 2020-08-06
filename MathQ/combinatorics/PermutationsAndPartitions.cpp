#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 998244353;
// https://codeforces.com/problemset/problem/1326/C
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0;i<n;++i) {
        cin >> a[i];
    }
    ll ans = (n*(n+1))>>1;
    ans -= ((n-k)*(n-k+1))>>1;
    //sum of highest k numbers is the maximum partition value possible
    //Since the first from both end which contributes to the max value must be the starting and ending points
    //Now how to compute such segments
    //Now every element can have segment of lengths (L) = 1(itself) + number of elements between itself and next segment point(excluding the end points from this count)
    //number of disjoint segments with max parition value = (L1  * L2 * L3 * L4 * ...........*L(k-1))

    int l = 0;
    int r = n-1;
    //trim both ends 
    while (a[l] <= (n-k)) ++l;
    while (a[r] <= (n-k)) --r;
    vector<ll> b(n+1, 0);
    for (int i=n-1;i>=0;--i) {
        if (a[i]>n-k) b[i] = 1;
        b[i] += b[i+1];
    }
    ll prev = r+1;
    ll count = 1;
    while (r >= l) {
        if (b[r] > b[r+1]) {
            ll num = prev - r;
            prev = r;
            count = (1LL * num *count)%mod;
        }
        --r;
    }
    cout << ans << " " << count <<"\n";
    return 0;
}