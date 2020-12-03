#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 998244353; 
const int maxn = 3e5+1;
ll fact[maxn];
void factorial(){
    fact[0] = 1;
    for(ll i = 1;i<maxn;++i){
        fact[i] = (fact[i-1] * i)%mod;
    }
}

ll power(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b>>=1;
    }
    return r;
}

ll ncr(ll n,ll r){
    ll answer = fact[n];
    answer = (answer * power(fact[r],mod-2LL))%mod;
    answer = (answer * power(fact[n-r],mod-2LL))%mod;
    return answer%mod;
}
// https://codeforces.com/problemset/problem/1444/B
int main(){
    factorial();
    int n;
    cin >> n;
    ll sum = 0;
    /*
        IDEA : SUM OF EVERY POSSIBLE is the same.
        Consider the elements of the array sorted.
        Then let partition1 will be from [1,n]
        and partition2 will be from [n+1,2*n].
        partition1 is in non-decreasing order
        partition2 is in non-increasing order
        So for every index i, there will be one value in partition1 and one in partition2.
        No matter how the partition is done, since the number elements is even 2*n,
        the pairing of values of partitions will always be the same.
        answer = (sum of elements in parition1 - sum of elements in parition2) *(number of possible partitions i.e. C(2*n,n)) ;
        */
    vector<ll> arr;
    for(int i = 0;i<2*n;++i){
        arr.emplace_back(0);
        cin >> arr.back();
    }
    sort(arr.begin(),arr.end());
    for(int i = 0;i<n+n-i-1;i++){
        sum+=abs(arr[i]-arr[n+n-i-1]);
        if(sum>=mod) sum-=mod;
        else if(sum<0) sum+=mod;
    }
    ll answer = ncr((ll)2*n,(ll)n);
    //cerr << answer << " " << sum <<"\n";
    answer = (answer * sum)%mod;;
    cout << answer <<"\n";
    return 0;
}