#include<bits/stdc++.h>
using namespace std;

/*
    Given a infinite strip of height 2.
    You are given infinite tiles of dimensions 2*1.
    For a given length n for strip.Find the number of ways to tile the strip with 2*1 or 1*2 tiles

*/

//F(n) = F(n-1) + F(n-2);
//F(1) = 1;
//F(2) = 2;

void multiply(int A[2][2],int B[2][2]){
    int R[2][2] = {{0,0},{0,0}};
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            for(int k = 0;k<2;k++){
                R[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }

    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            A[i][j] = R[i][j];
        }
    }
}

void pow(int A[2][2],int n){
    int R[2][2] = {
        {1,0},{0,1}
    };

    while(n!=0){
        if(n&1){
            multiply(R,A);
        }
        n >>=1;
        multiply(A,A);
    }
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            A[i][j] = R[i][j];
        }
    }
}

void powRec(int A[2][2],int n){
    if(n == 0) return;
    int M[2][2] = {{1,1},{1,0}};
    pow(A,n>>1);
    multiply(A,A);
    if(n&1)
    multiply(A,M);
}

int main(){
    int n = 15;
    /*O(n)*/
    int dp[n+1];
    dp[0] = 0;//number of ways to tile the strip of length 0
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3;i<=n;i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout<<dp[n]<<"\n";
    /* O(logn) solution*/
    int a = 1;
    int b = 2;
    int A[2][2] = {{1,1},{1,0}};
    pow(A,n-2);
    int ans = b*A[0][0] + a*A[0][1];
    cout<<ans<<"\n";
    return 0;
}