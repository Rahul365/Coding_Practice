#include<bits/stdc++.h>
using namespace std;
const int magic = 70;

int main(){
    //two condition to check for good sequences:
    //1)sum of bits is even(must be true to check for 2nd condition)
    //2) 2*max <= sum or max <= sum-max , here max => maximum number of set bits in a number
     //Notice maximum number of set bits possible in a number are 61 only a[i] = 10^18
    //So 2nd condition max <= sum - max will not be true for longest intervals of sequences
    //Condition will hold true for intervals of [i to i + 70] 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n),pref(n);
    for(int i = 0;i<n;++i){
        long long x;
        cin >> x;
        a[i] = __builtin_popcountll(x);
        pref[i] = a[i];
        if(i!=0)
            pref[i] += pref[i-1];
    }
    
    long long ans = 0;
    int even = 0;
    int odd  = 0;
    //count all the even and odd numbers
    for(int i = 0;i<n;++i){
        if(pref[i]&1) ++odd;
        else ++even;
    }
    ++even;//for empty prefix
    //pair even with even 
    //odd with odd
    auto f = [&](int x){return (long long )x *(x-1)/2;};
    
    
    ans = f(even) + f(odd);
    
    for(int i = 0;i<n;++i){
        int mx = 0;
        int sum = 0;
        for(int j =i;j < min(n,i+magic);++j){
            sum += a[j];
            mx=max(mx,a[j]);
            if(sum%2== 0 && !(mx <= sum-mx))  --ans;
        }
    }
    cout <<ans<<"\n";
    return 0;
}