#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
using lld = long double;
lld power(lld a , int b){
    lld  r = 1.0;
    while(b){
        if(b&1) r = r * a;
        a = (a * a);
        b >>= 1;
    }
    return r;
}
// https://codeforces.com/problemset/problem/518/D
/*Read the editorial for this one*/
int main(){
    int n,t;
    lld p;//probability that the person will enter the escalator 
    cin >> n >> p >>  t;
    lld dp[t+1][n+1];//dp[TimeInSeconds][#OfPeople]
    /*Forward DP*/
    /*
    memset(dp,0.0,sizeof dp);
    dp[0][0] = 1;//base likelihood
     for(int i = 0;i<t;++i)
         for(int j =0;j<=n;++j){
             if(j == n){
                 dp[i+1][j] += dp[i][j];
             }
             else{
                 dp[i+1][j+1] += dp[i][j] * p;
                 dp[i+1][j] += dp[i][j] * (1-p);
             }
         }
    */
    // for(int i = 0;i<=t;++i)for(int j = 0;j<=n;++j) cerr << dp[i][j] <<" \n"[j==n];
    /*backward Dp*/
    memset(dp,0.0,sizeof dp);
    dp[0][0] = 1;//base likelihood
    for(int i = 1;i<=t;++i){
        for(int j = 0;j<=n;++j){
            if(j == n){
                dp[i][j] += dp[i-1][j] + dp[i-1][j-1] * p;
            }
            else{
                if(j)
                dp[i][j] += dp[i-1][j-1] * p;
                dp[i][j] += dp[i-1][j] * (1-p);
            }
        }
    }
    // for(int i = 0;i<=t;++i)for(int j = 0;j<=n;++j) cerr << dp[i][j] <<" \n"[j==n];
    lld answer = 0;//SUM(dp[t][j=0...n] * j) is the expected number of peoples that will be standing on the escalator after t seconds

    for(int j = 0;j<=n;++j) answer += j * 1.0 * dp[t][j];
    cout <<fixed << setprecision(4) <<  answer <<"\n";
    return 0;
}
