#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 1e9+7;
// https://codeforces.com/problemset/problem/152/C
/**
 * from editorial :
 * while solving this problem, one thing to notice is that
 * we can do the given operation in such a way that it is possible to get any of n names character at some index in the new name also
 * e.g.
 * new_name[m=4] = { [s[0][1<=id0<=m], s[1][1<=id1<=m] ,s[2][1<=id2<=m] , s[3][1<=id3<=m] }
*/
int main(){
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for(int i = 0;i<n;++i) cin >> s[i];
    bool mark[26];
    ll answer = 1;
    for(int pos = 0;pos < m;++pos){
        memset(mark,false,sizeof mark);
        ll v = 0;
        for(int i = 0;i<n;++i){
            if(mark[s[i][pos]-'A']) continue;
            ++v;
            mark[s[i][pos]-'A'] = true;
        }
        answer = (v*answer)%mod;
    }
    cout << answer <<"\n";
    return 0;
}
