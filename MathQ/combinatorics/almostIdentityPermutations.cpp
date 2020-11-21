#include<bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i = 0;i<(int)n;++i)
using ll = long long int;
const ll mod = 1e9+7;
ll ncr[1010][1010];
ll D[1010];/*
number of derangements => D[n] = n! * SUM(((-1)^r)/r!);
Recursive formula =>
D[n] = n * D[n-1] + (-1)^n;
*/
void compute(){
    ncr[0][0] = 1;
    D[0] = 1;
    for(int i = 1;i<=1000;++i){
        D[i] = (i*D[i-1]) + (i&1?-1:1);
    }
    for(int i = 1;i<=1000;++i){
        ncr[i][0] = ncr[i][i] = 1;
        for(int j = 1;j<i;++j){
            ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
        }
    }
    // for(int i = 0;i<=5;++i){
    //     for(int j = 0;j<=i;++j)
    //     cerr << ncr[i][j] <<" \n"[j==i];
    // }
}
// https://codeforces.com/problemset/problem/888/D
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    compute();
    int n,k;
    cin >> n >> k;
    ll answer = 0;
    FOR(derangements,k+1){
        // cerr <<derangements<<" : "<<D[derangements] << " " << ncr[n][derangements] <<"\n";
        answer += D[derangements] * ncr[n][derangements];
    }
    cout << answer <<"\n";
    return 0;
}