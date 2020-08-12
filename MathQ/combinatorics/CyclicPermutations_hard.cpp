#include<bits/stdc++.h>
using namespace std;
const long long int mod = 1e9+7;
// https://codeforces.com/problemset/problem/1391/C
int main(){
    long long int n;
    scanf("%lld",&n);
    //answer = n! - (2^(n-1))
    long long int ans = 1;
    long long int sub = 1;
    for(long long int i = 1;i<=n;++i){
        ans *= i;
        if(i < n) sub *= 2;
        sub %=mod;
        ans %= mod;
    }
    ans = ((ans - sub)%mod + mod )%mod;
    printf("%lld\n",ans);
    return 0;
}