#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1400/D
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<long long int> cntR(n*n,0);
        for(int i = 0;i<n;++i){
            cin >> a[i];
            --a[i];
        }
        /*
          Tags : combinatorics and implementation
          Trick is to focus on one pair at a time
          Just need to count the equal pairs (a[i],a[j]) = (a[k],a[l]) , i < j < k < l
          for(j = n-1;j>=0;--j){
            count(a[k],a[l]) where k = j+1, k < l < n
            answer += count(a[i],a[j]) where 0<i<j
          }
          O(n*n) 
          Tricky approach
        */
        long long int answer = 0;
        for(int j = n-1;j>=0;--j){
            int k = j+1;
            for(int l = k+1;l < n;++l){
                cntR[a[k] * n + a[l]]++;
            }
            for(int i = 0;i  < j;i++){
                answer += cntR[a[i] *  n + a[j]];
            } 
        }
        cout << answer <<"\n";
    }
    return 0;
}