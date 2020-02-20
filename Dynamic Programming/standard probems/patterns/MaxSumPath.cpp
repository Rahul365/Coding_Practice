#include<bits/stdc++.h>
using namespace std;
/**
 * Given a matrix of n x m, each cell contains a value.
 * calculate the max path sum value to reach cell(n-1,m-1) from cell(0,0).
 * you will start at cell(0,0).
 * Only permissible move you can make is go either right/down from a cell
*/
int n,m;
const int N = 1004;
int mat[N][N];
int dp[N][N];

/*Memoization DP*/
int getmaxSumPath(int x,int y){
    if(x >= n || y >= m)
        return 0;

    int &ans = dp[x][y];
    if(ans != INT_MIN){
        return ans;
    }
    
    ans = mat[x][y] + max(getmaxSumPath(x+1,y),getmaxSumPath(x,y+1));
    return ans;
}

int getMaxSumPathII(int x,int y){
    dp[0][0] = mat[0][0];
    for(int i = 1;i<m;i++){
        dp[0][i] = mat[0][i] + dp[0][i-1];
    }
    for(int i = 1;i<n;i++){
        dp[i][0] = mat[i][0] + dp[i-1][0];
    }

    for(int i = 1;i<n;i++){
        for(int j = 1;j<m;j++){
            dp[i][j] = mat[i][j] + max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n-1][m-1];
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j =0;j<m;j++){
            dp[i][j] = INT_MIN;
            cin>>mat[i][j];
        }
    }
    cout<<getmaxSumPath(0,0)<<"\n";
    cout<<getMaxSumPathII(0,0)<<"\n";
    return 0;
}
/**
 * 
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
OUTPUT : 73
 * 
*/