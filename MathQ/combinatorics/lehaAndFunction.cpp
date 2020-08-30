#include<bits/stdc++.h>
#define rep(i,n) for(int i = 0;i<n;++i)
using namespace std;
// https://codeforces.com/problemset/problem/840/A
/*
     Just read some comment for this probem under the contest post
     F(n,k)->Not clearly understandable through editorial either
*/
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> m;
    vector<int> a(m),b(m);
    rep(i,m) cin >> a[i];
    rep(i,m) cin >> b[i];
    vector<pair<int,int>> bb;
    rep(i,m) bb.push_back({b[i],i});
    sort(a.begin(),a.end(),greater<int>());
    sort(bb.begin(),bb.end());
    vector<int> a_new(m);
    rep(i,m){
        a_new[bb[i].second] = a[i];
    }
    rep(i,m) cout << a_new[i] << " "; cout <<"\n";
    return 0;
}