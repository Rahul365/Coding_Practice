#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 998244353;
const int maxn = 3e5+11;
//https://codeforces.com/problemset/problem/1420/D
ll fact[maxn];
ll invfact[maxn];
void bruteforce(int n,int k){
    vector<pair<int,int>> lmp;
    for(int i =0 ;i<n;++i){
        int x,y;
        cin >> x >> y;
        lmp.emplace_back(x,y);
    }
    // Brute force
    function<ll(int,int,int,int)> rec = [&](int pos,int l,int r,int k){
        if(k == 0) return 1LL;
        if(pos == n) return 0LL;
        if(l > r || lmp[pos].first > r || lmp[pos].second < l) return 0LL;
        return rec(pos+1,max(lmp[pos].first,l),min(lmp[pos].second,r),k-1)%mod
        + rec(pos+1,l,r,k)%mod;
    };
    ll answer = 0;
    for(int i = 0;i<=n-k;++i){
        answer += rec(i+1,lmp[i].first,lmp[i].second,k-1);
        answer %= mod;
    }
    cout << answer <<"\n";
}

ll powermod(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1) r = (r*a)%mod;
        a = (a * a)%mod;
        b >>= 1LL;
    }
    return r;
}

void compute(){
    fact[0] = 1LL; invfact[0] = 1LL;
    for(ll i = 1;i<maxn;++i){
        fact[i] = (fact[i-1] * i * 1LL)%mod;
        invfact[i] = powermod(fact[i],mod-2LL);
    }
}

ll nCr(ll n,ll r){
    if(n < r) return 0LL;
    return (fact[n]%mod * invfact[n-r]%mod * invfact[r]%mod)%mod;
}

int main(){
    compute();
    int n,k;
    scanf("%d%d",&n,&k);
    /*Event setup*/
    ll events[2*n];
    for(int i = 0;i  < n;++i){
        scanf("%lld %lld",&events[i],&events[n+i]);
        events[i]*=2;//even number represents the opening of an interval
        events[i+n]*=2;
        events[i+n]+=1;//odd number represents closing of an interval
    }
    sort(events,events+(2*n));
    ll answer = 0;
    ll onlamps = 0;
    for(int r = 0;r < 2*n;){
        int l = r;
        while(r<2*n && events[l] == events[r]){
            ++r;
        }
        ll newlamps = r - l;
        if(events[l]&1){
            onlamps -= newlamps;
        }
        else{
            answer = (nCr(onlamps + newlamps,(ll)k) + answer)%mod;
            answer = (answer - nCr(onlamps,k)+mod)%mod;
            onlamps += newlamps;
        }
    }
    printf("%lld\n",answer);
    return 0;
}