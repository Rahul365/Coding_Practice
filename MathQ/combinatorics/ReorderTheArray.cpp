#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1007/A


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0;i<n;++i) cin >> a[i];
    multiset<int> s;
    for(int v : a) s.insert(v);
    int ans = 0;
    for(int i = 0;i < n;++i) {
        auto it = s.upper_bound(a[i]);
        if(it!=s.end()){
            ++ans;
            s.erase(it);
        }
    }
    cout << ans <<"\n";
    return 0;
}