#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 1;
/*
  44 lis = lis(4) + lis(4)
  47 lis = lis(4) + lis(7)
  74 lis = lis(7) + lis(4)
  77 lis = lis(7) + lis(7)

*/
/*
7 10
7474747
count
count
switch 1 7
count
switch 1 1
switch 3 3
switch 5 5
count
switch 1 7
count
*/
/**
 * TLE
 * O(n^2) per count query
 * O(n) update
*/
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    int a[n];
    string s;
    cin >> s;
    int dp[n];
    int op[n];
    memset(op,0,sizeof op);
    memset(dp,0,sizeof dp);
    for(int i= 0;i<n;++i){
        a[i] = s[i]=='7';
    }
    while(q--){
        string x;
        cin >> x;
        if(x == "switch"){
            int l,r;
            scanf("%d%d",&l,&r);
            --l,--r;
            for(int i = l;i<=r;++i)
                a[i] = 1 - a[i];
        }
        else{
            int ans = 1;
            memset(dp,0,sizeof dp);
            for(int i = 0;i<n;++i)
            {
                dp[i] = 1;
                for(int j = 0;j<i;++j){
                    if(a[i] >= a[j] && dp[i] < 1 + dp[j])
                        dp[i] = 1 + dp[j];
                }
                ans = max(ans,dp[i]);
            } 
            cout << ans <<"\n";
        }
    }
    return 0;
}