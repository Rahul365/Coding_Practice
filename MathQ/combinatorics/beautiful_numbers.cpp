#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 1e6+2;
const int mod = 1e9+7;
ll fact[maxn];
// https://codeforces.com/problemset/problem/300/C
bool isexcellent(int num,int a,int b){
    while(num){
        if(!(num % 10 == a || num%10 == b)) return false;
        num /= 10;
    }
    return true;
}

ll pmod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1) r = (r * a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fact[0] = 1LL;
    for(int i = 1;i<maxn;++i) fact[i] = (i * fact[i-1])%mod;
    int a,b,n;
    cin >> a >> b >> n;
    ll answer = 0;
    for(int cnt_a = 0;cnt_a <= n;++cnt_a){//frequency of 'a' digit in the number,(n-cnt_a) be the frequency of 'b' digit in the number
        if(isexcellent((cnt_a * a)+ ((n-cnt_a)*b) , a,b)){//check if the sum is excellent
            //cout << cnt_a << " " << (n-cnt_a) <<"\n";
            //answer = sum[ P(n,n)/(cnt_a! *(n-cnt_a)!)] %mod
            answer += (fact[n]%mod * pmod(fact[cnt_a],mod-2)%mod * pmod(fact[n-cnt_a],mod-2)%mod)%mod;
            answer %= mod;
        }
    }
    cout << answer <<"\n";
    
    return 0;
}