#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int MAXN = 1e5+2;

int memo[MAXN];
int countways(string s,int n){
   if(n == 0) return 1;
   if(s[n-1] == 'w' || s[n-1] == 'm') return 0;
   int &ways = memo[n];
   if(ways != -1)
        return ways;
   ways = 0;
   if(n>=2 && (s[n-1] == 'u' || s[n-1] == 'n')){
       string t = s.substr(n-2,2);
       
       if(t == "uu" || t == "nn"){
           ways = (ways + countways(s,n-2))%mod;
       }
   }
   ways = (ways + countways(s,n-1))%mod;
   return ways;
}

int countwayslinear(string s,int n){
    for(int i = 0;i<n;i++)
        if(s[i]=='w' || s[i] == 'm')
            return 0;
    int dp[n+1];
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2;i<=n;i++){
        dp[i] = (dp[i] + dp[i-1])% mod;
        // if(s[i-1] == 'w' || s[i-1] == 'm') return 0;
        if(s[i-1] == s[i-2]  && (s[i-1] == 'n' || s[i-1] == 'u')){
                dp[i] = (dp[i] + dp[i-2])%mod;
        }
    }
    return dp[n];
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    memset(memo,-1,sizeof(memo));
    string s;
    cin>>s;
    cout<<countwayslinear(s,s.length())<<"\n";
    return 0;
}