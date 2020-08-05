#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/459/B
int main(){
    int n;
    cin >> n;
    map<ll,ll> b;
    for(int i = 0;i<n;++i)
    {
        ll x;
        cin >> x;
        ++b[x];
    }
    //maximum difference is between the minimum and maximum value
    //and the number of pairs = (frequency of minimum * frequency of maximum);
    //if difference == 0 then count = (freq(minimum)*(freq(minimum)-1))>>1;
    ll maxdiff = b.rbegin()->first - b.begin()->first;
    ll count = 0;
    if(b.size() > 1) count = b.begin()->second * b.rbegin()->second;
    else count = (b.begin()->second*(b.begin()->second-1))>>1;
    cout << maxdiff << " " << count <<"\n";
    return 0;
}