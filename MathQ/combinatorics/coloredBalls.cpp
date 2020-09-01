#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int maxn = 1e3+12;
using ll = long long int;
// https://codeforces.com/problemset/problem/553/A
/*
Since mod is prime so we can Fermat little theorem
 a = a^m mod m
 1 = a^(m-1) mod m
 where m is prime
 a^-1 = a^(m-2) mod m
*/
ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1) r = (r * a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return r;
}

void solveUsingModularInverse(vector<int> &c){
    ll answer = 1;
    ll total = 0;
    int n = c.size();
    long long p = 1;
    for(int i = 0;i<n;++i){
        if(c[i]-1==0) {++total; continue;}
        total += c[i];//number of objects to choose from 
        //permutate c[i]-1 objects
        ll r = c[i]-1;
        ll curr = 1;
        ll N = total-1;
        ll d = 1;
        while(r){
            curr *= N;
            curr %= mod;
            d *= r;
            d %= mod;
            --N;
            --r;
        }
        curr = (curr%mod * pmod(d,mod-2))%mod;
        // cerr << curr << " " << total-1 <<" " << c[i]-1 <<" "<<d << "\n";
        answer = (answer * curr)%mod;
    }
    cout << answer <<"\n";
}

ll comb[maxn][maxn];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    memset(comb,0LL,sizeof comb);
    comb[0][0] = 1;
    for(int i = 1;i<=1000;++i){
        comb[i][0] = 1;
        for(int j = 1;j<=i;++j){
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j])%mod;    
        }
    }
    int n;
    cin >> n;
    vector<ll> c(n);
    for(int i = 0;i<n;++i) cin >> c[i];
    
    ll answer = comb[c[0]-1][c[0]-1];
    for(int i = 1;i<n;++i){
        answer = (answer * comb[c[i]-1 +c[i-1]][c[i]-1])%mod;
        c[i] += c[i-1];    
    }
    cout << answer <<"\n";
    return 0;
}