#include<bits/stdc++.h>
using namespace std;
const int MAX = 10000;
/**
 * Find the minimum number of squares to represent given number N.
 * eg N = 2 -> 2 -> (1^2 + 1^2)
 *    N = 13 -> 2 -> (3^2 + 2^2)
 *    N = 5 -> 2 ->(2^2 + 1^2)
 * 
 * Solution : To represent the number in form of sum of squares, the coins must be in range 0 to sqrt(n)
 */
int table[10000];
int min_num_squares_rec(int N){
    if(N == 0) return 0;

    int &ans = table[N];
    if(ans != -1)
        return ans;
    ans = N;

    for(int coins = 1;coins<=sqrt(N);++coins){
        if(N >= coins*coins)
        ans = min(1 + min_num_squares_rec(N-(coins*coins)),ans);
    }
    return ans;
}

int min_num_squares(int N){
    int dp[N+1];
    memset(dp,N,sizeof(dp));
    dp[0] = 0;//0 squares are needed to represent 0;

    for(int coin = 1;coin<=sqrt(N);coin++){
        for(int S = coin*coin ; S<=N; S++){
                dp[S] = min(1 + dp[S-(coin*coin)],dp[S]);
        }
    }
    return dp[N];//minmum number of squares needed to represent number N
}

int main(){
    memset(table,-1,sizeof(table));
    table[0] = 0;
    cout<<min_num_squares_rec(13)<<"\n";
    cout<<min_num_squares_rec(7)<<"\n";
    cout<<min_num_squares_rec(5)<<"\n";
    return 0;
}