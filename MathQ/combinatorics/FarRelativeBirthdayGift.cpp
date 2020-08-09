#include<bits/stdc++.h>
#define rep(i,n) for(int i =0 ;i<n;++i)
using namespace std;
// https://codeforces.com/problemset/problem/629/A
int main(){
    int n;
    cin >> n;
    vector<vector<int>> cake(n,vector<int>(n,0));
    rep(i,n){
        string s;
        cin >> s;
        rep(j,n)
        {
            cake[i][j] = (s[j] == '.'?0:1);
        }
    }
    /*Handshake lemma*/
    auto count = [&](long long int num){
        return (num * (num-1))>>1;
    };

    long long int ans = 0;
    //count pairs for each row
    rep(r,n){
        long long int sum_row_wise = 0;
        long long int sum_col_wise = 0;
        rep(c,n){
            sum_row_wise += cake[r][c];        
            sum_col_wise += cake[c][r];
        }
        ans += count(sum_row_wise) + count(sum_col_wise);
    }   
    cout << ans <<"\n";
    return 0;
}