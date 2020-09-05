#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll  mod = 998244353;
// https://codeforces.com/problemset/problem/1327/E
ll pmod(ll a,ll b)
{
    ll r = 1;
    while(b){
        if(b&1) r = (r * a)%mod;
        a = (a * a)%mod;
        b >>= 1;
    }
    return r;
}
// https://codeforces.com/problemset/problem/1312/D
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    ll fact[m+2];
    fact[0] = 1LL;
    for(ll i = 1;i<=m;++i){
        fact[i] = (i*fact[i-1])%mod;
    }
/**
 * Targeted array will have n-1 distint elements
 * 1) C(m,n-1) ways to choose n-1 distinct elements combination from the m elements
 * 2) We can't pick the larget of (n-1) elements as duplicate (as it voilates the strict unimodal conditions
 * ....< a[i] < a[i+1] > a[i+2] > a[i+3]> ....),so there are (n-2) elements from which we can choose an element and write it two times in the final array (1 on left of Largest element and other on the right)
 * 3) Rest there will be (n-3) positions left to fill. As each element will have a choice of either going in the left or in the right.
 * So there will be total of 2^(n-3) ways to fill the rest of (n-3) positions
 * Answer = C(m,n-1) * (n-2) * 2^(n-3)
 * 
*/
    if(n == 2){
        cout << 0 <<"\n";
        return 0;
    }
    ll answer = pmod(2LL,(ll)n-3);
    answer = (answer * (n-2))%mod;
    //Since mode is prime value , so we can compute inverse of the fact[n-1] and fact[m-n+1]
    //and compute it (fact[m] * inv(fact[n-1]) * inv(fact[m-n+1]))%mod
    ll ncr = (fact[m] * pmod(fact[n-1],mod-2))%mod;
    ncr = (ncr * pmod(fact[m-n+1],mod-2))%mod;
    answer = (answer * ncr)%mod;
    cout << answer <<"\n";
    return 0;
}