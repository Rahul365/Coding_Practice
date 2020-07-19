#include<bits/stdc++.h>
using namespace std;

/*
    MINIMAX, DYNAMIC PROGRAMMING
    https://leetcode.com/problems/guess-number-higher-or-lower-ii/
*/
class Solution {
    const int INF = 1e9+7;
    int **mem;
public:
    int pick(int l,int r){
        int &ans = mem[l][r];
        if(l == r) return ans = 0;
        if(ans != INF) return ans;
        for(int i = l;i<=r;++i){
            int sub = i + max(l>=i-1?0:pick(l,i-1),i+1>=r?0:pick(i+1,r));
            ans = min(ans,sub);
        }
        return ans;
    }
    
    int pickI(int n){
        mem = new int*[n+1];
         for(int i = 0;i<=n;++i){
             mem[i] = new int[n+1];
             for(int j = 0;j<=n;++j){
                 mem[i][j] = INF;
             }
         }
         return pick(1,n);
    }
    
    /*Minimizing the maximum possible loss*/
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int len = 1;len<=n;++len){
            for(int l = 0;l<=n-len;++l){
                int r = l+len-1;
                if(l == r){
                    dp[l][r] = 0;
                }
                else if(len == 2){
                    dp[l][r] = min(l+1,r+1);
                }
                else{
                    dp[l][r] = INF;
                    for(int p = l;p<=r;++p){
                        dp[l][r] = min(dp[l][r]
                                       ,p+1 + max(l>=p-1?0:dp[l][p-1],p+1>=r?0:dp[p+1][r]));
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
};