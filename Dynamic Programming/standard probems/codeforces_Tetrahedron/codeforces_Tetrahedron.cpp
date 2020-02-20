#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int N = 1e7+1;

int dp[2][N];
bool vis[2][N];

/*
Memoization
MLE (memory limit exceeded)*/
int getways(int src,int dest,int n){
    // int dp[4][N];
    // bool vis[4][N];
    if(n == 0){
        return (src == dest)?1:0;
    }
    int &ans = dp[src][n];
    if(vis[src][n])
        return ans;
    vis[src][n] = true;
    for(int i = 0;i<4;i++){
        if(i == src) continue;
        ans = (ans+getways(i,dest,n-1))%mod;
    }
    return ans;
}

/**
 * O(2*N) MLE
 */ 
int getwaysdp(int same,int n){
    if(n == 0){
        return same;
    }

    int &ans = dp[same][n];
    if(vis[same][n]){
        return ans;
    }
    vis[same][n] = true;
    if(same == 0){
        ans = (2LL*getwaysdp(same,n-1) + getwaysdp(1-same,n-1))%mod;
    }
    else{
        ans = (3LL*getwaysdp(1-same,n-1))%mod;
    }
    return ans;
}

/*O(2*N) solution Accepted*/
int getwaysdpII(int steps){
    dp[1][0] = 1;//there is only one way to start and end same vertex with 0 steps
    for(int i = 1;i<=steps;i++){
        dp[1][i] = (3LL*dp[0][i-1])%mod;
        dp[0][i] = (2LL*dp[0][i-1] + dp[1][i-1])%mod;
    }
    return dp[1][steps];
}


int main(){
    cout<<getwaysdpII(3)<<"\n";
    return 0;
}