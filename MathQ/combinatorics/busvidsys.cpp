#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/978/E
int main(){
    int n; ll w;
    scanf("%d%lld",&n,&w);
    vector<ll> a(n+1);
    vector<ll> relations(n+1);
    for(int i = 1;i<=n;++i){
        ll diff;
        scanf("%lld",&diff);
        relations[i] = diff;
        a[i] = diff + a[i-1];
    }
    /**
     * We are given the difference between the #of passengers in the bus between before and after every bus stop
     * e.g. There are x # of passengers in the bus. After bus stop A, there will be y # of passengers in the bus
     * So a[i] = y-x , for ith bus stop
     * 
     * Idea to solve this problem : 
     * let's view the array as
     * _ a[i] _ a[i]+a[i-1] _ a[i]+a[i-1]+a[i-2] _ ......
     * Here '_' are bus-stops
     * So first build the prefix sum of array a[]
     * We need to find the 'base' value for the number of passengers in the bus such that prefix(a[0..i])+base >= 0
     * Note : base value can be find using Binary search (as 1 <= n <= 1000) in O(n*log(w))
     * if(no such base exists) answer = 0
     * if(base exists)
     *  (There is still a possibility that answer don't exist)
     *  initially, upperbound for base value when bus is enroute will 'w' itself
     *  Now, How to decide the upperbound for the bus when crossing ith station
     *  Two cases to be taken into account here : 
     *  1) a[i] < 0, i.e. the difference between after and before count is negative
     *     So upperbound computed at ith busstop = prevbound + a[i] ( < w)
     *  2) a[i] >= 0,i.e. the difference between after and before count is positive, so the passenger increases after ith busStop
     *     So upperbound computed at ith busstop = min(w,prevbound + a[i]) 
     *  if(prefix(a[0..i]+base) > upperbound at ith bustop) answer = 0
     *  else answer = max(answer,count(prefix(a[0..i],upperbound))
     */
    
    auto check = [&](ll key){
        for(int i = 0;i<=n;++i){
            if(a[i]+key < 0) return false;
        }
        return true;
    };
    ll l = 0;
    ll r = w;
    ll base = -1;
    while(l <= r){
        ll m = l+(r-l)/2;
        if(check(m)){
            base = m;
            r = m-1;
        }
        else{
            l = m+1;
        }
    }

    if(base==-1){
        printf("0\n");
        return 0;
    }
    ll answer = 1e18L;
    for(int i = 0;i<=n;++i){
        a[i] += base;
    }
    ll prev = (relations[1] >= 0?w-relations[1]:w);
    auto range = [&](ll l,ll r)
    {
        if(l > r) return (ll)0;
        return  r-l+1;
    };
    for(int i = 1;i<=n;++i){
        ll curr = 0;
        if(relations[i] < 0){
            curr = prev + relations[i];
        }   
        else{
            curr = min(w,prev+relations[i]);
        }
        answer = min(answer,range(a[i],curr));
        prev = curr;
    }
    printf("%lld\n",answer);
    return 0;
}