#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 2004;
const ll mod = 998244353;
// https://codeforces.com/problemset/problem/1081/C
vector<ll> fact(maxn,0);
vector<vector<ll>> pascal(maxn,vector<ll>(maxn,0));
void computefact(){
    fact[0] = 1LL;
    for(int i = 1;i<maxn;++i){
        fact[i] = (fact[i-1] * i )%mod;
    }
    
}
void computePascal(){
    pascal[1][1] = 1;
    for(int i = 2;i<maxn;++i){
        pascal[i][1] = pascal[i-1][1];
        for(int j = 2;j<maxn;++j){
            pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
            if(pascal[i][j] >= mod){
                pascal[i][j] -= mod;
            }
            else if(pascal[i][j] < 0){
                pascal[i][j] += mod;
            }
        }
    }

    // for(int i = 1;i<=10;++i)for(int j = 1;j<=i;++j)cerr << pascal[i][j] <<" \n"[j==i];
}

ll pmod(ll a,ll b){
    ll r = 1LL;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1;
    }
    return r;
}

void doMath(ll n,ll m,ll k){
    computefact();
    ll answer = ((fact[n-1]%mod * pmod(fact[k],mod-2)%mod)%mod * pmod(fact[n-k-1],mod-2)%mod)%mod;
    answer = (answer%mod * m%mod * pmod(m-1,k)%mod)%mod;
    printf("%lld\n",answer);
}

int main(){
    computePascal();
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    //answer = C(n-1,k) * m * (m-1)^k
    ll answer = (pascal[n-1 + 1][k + 1] * m)%mod;
    answer = (answer * pmod(m-1,k))%mod;
    printf("%lld\n",answer);
    return 0;
}