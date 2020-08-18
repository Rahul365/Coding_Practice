#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < n; ++i)
using namespace std;
const int mod = 998244353;
// https://codeforces.com/problemset/problem/1178/C
int main()
{
    int w, h;
    scanf("%d%d", &w, &h);
    long long int r = 1;
    long long int s = 2;
    long long int p  = w + h;
    //answer is 2^(w+h) % mod (Quick guess based on the two test cases)
    //I don't know the proof before submission
    /*
        Proof:
        It can be observed that tile at position (i,j) can be placed uniquely depending on the tile(i-1,j) and(i,j-1).
        So once all the tiles at (1,i) and (j,1) are placed the rest of the tiles can be placed uniquely.
        Thus tile (1,1) can be placed in 4 ways and rest of the tiles (1,i) and (j,1) can be placed in 2 way each.
        4 * 2^(w+h-2) ways to place tiles in the w*h grid.
        answer = 2^2 * 2^(w+h-2)
               = 2^(w+h)

        Time complexity : O(logw + logh) => O(log(w+h))
    */
    while(p){
        if(p&1){
            r = (1LL * r * s)%mod;
        }
        s = (s*s)%mod;
        p >>= 1;
    }
    printf("%lld\n",r);
    return 0;
}