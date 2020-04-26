#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 998244353;
vector<int> a(4000);
int n,s;
ll dp[4000][4000][3];
int ways(int l,int r,int S){
    if(S == 0){
        return 1;
    }
    if(r == l){
        return 0;
    }
    return ways(l,r-1,S) + (S>=a[r-1]?ways(l,r-1,S-a[r-1]):0);
}



int main(){
    cin >> n >> s;
    for(int i = 0;i<n;++i){
        cin >> a[i];
    }
   
    /*
     int ans  = 0;
    for(int i = 0;i<n;++i){
        for(int j = i;j < n;++j){
            ans += ways(i,j+1,s);
            if(ans >= mod){
                ans-=mod;
            }
        }
    }
    
    cout << ans <<"\n";
    */
   auto add =[&](ll &x,ll y){
       x += y;
       x %= mod;
   };
   
   memset(dp,0LL,sizeof dp);
   dp[0][0][0] = 1;
   for(int i = 0;i<n;++i){
       for(int j = 0;j<=s;++j){
            add(dp[i+1][j][0],dp[i][j][0]);
            add(dp[i+1][j][1],dp[i][j][0]+dp[i][j][1]);
            add(dp[i+1][j][2],dp[i][j][0]+dp[i][j][1]+dp[i][j][2]);
            if(j + a[i] <= s){
                add(dp[i+1][j+a[i]][1],dp[i][j][0] + dp[i][j][1]);
                add(dp[i+1][j+a[i]][2],dp[i][j][0] + dp[i][j][1]);
            }  
       }
   }
   cout << dp[n][s][2] <<"\n";
    return 0;    
}