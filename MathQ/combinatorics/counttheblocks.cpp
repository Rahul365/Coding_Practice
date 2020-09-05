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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    /**
     * Counting of blocks of lengthe len can be of two types : 
     * 1) First one is where place the block at start or the end.
     *    2 choices of positions for the block
     *    10 choices for choosing a value for the block of length len, x = pick({0-9})
     *    9 choices for choosing a value for the adjacent element , pick({0-9} - x)
     *    10^(n-len-1) choices for choosing the value for the remaining number of elements
     *    Total number of ways to do so = (2 * 10 * 9 * 10^(n-len-1))
     * 2) Second type is where we don't place the block at the start or at the end
     *    Instead block of length len is placed like this = {({0-9}-x),(x={0-9}),({0-9}-x)}
     *    So we want to place the block of length surrounded by 2 adjacent elements not equal to block value
     *    Thus we have (n-(len+2))+1 choices to place such block
     *    10 -> choices for choosing a value for the block of length len,x = pick({0-9})
     *     9 -> choices for choosing a value for the adjacent element to the left of block,pick({0-9}-x)
     *     9 -> choices for choosing a value for the adjacent element to the right of block, pick({0-9}-x)
     *    10^(n-len-2) choices for choosing a value for the rest of the elements left
     *    n-len-2+1 -> choices of positions for the block
     *    Total number of ways to count such numbers = (n-len-2+1)*10*9*9*10^(n-len-2)
     * Special case for block length len = n, answer is 10
    */
    for(ll len = 1;len<=n;++len){
        ll answer = 10LL;
        if(len < n){
            ll A = (2LL * pmod(10LL,n-len) * 9LL)%mod;
            ll B = ((n-len-1)*9LL*9LL*pmod(10LL,n-len-1))%mod;
            answer = (A + B)%mod;
        }
        cout << answer <<" \n"[len==n];
    }
    return 0;
}