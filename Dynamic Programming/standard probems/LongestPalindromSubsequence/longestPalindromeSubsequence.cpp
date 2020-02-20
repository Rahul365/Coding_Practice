#include<bits/stdc++.h>
using namespace std;
/**
 * Given a sequence of characters a1,a2,a3,........,an.
 * Find the length of longest palindrome subsequence for the given sequence.
*/

int memo[1000][1000];//plugging memo dp
int max_length(string s,int i,int j){
    if(i > j){
        return 0;
    }
    if(i == j)
        return 1;
    
    int &ans = memo[i][j];
    if(ans!=-1){
        return ans;
    }

    if(s[i] == s[j]){
        ans =  2 + max_length(s,i+1,j-1);
    }
    else
        ans =  max(max_length(s,i+1,j),max_length(s,i,j-1));
    return ans;
}

int max_length_linearDP(string s,int n){
    int dp[n][n];
    
    //base cases
    //for each i dp[i][i] = 1;
  
  
    for(int i = 0;i<n;i++)
        dp[i][i] = 1;

    for(int k =2;k<=n;k++){
       for(int i = 0;i<n-k+1;i++){
           int j = i + k -1;
           if(s[i] == s[j] && k == 2)
            {
                dp[i][j] = 2;
            }
            else if(s[i] == s[j]){
                dp[i][j] = 2  +dp[i+1][j-1];
            }
            else{
                dp[i][j] = max(dp[i+1][j],dp[i][j-1]);
            }
       }
    }

    return dp[0][n-1];
}


int main(){
    string s = "GEEKSFORGEEKS";
    int n = s.length();
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            memo[i][j] = (i==j)?1:-1;
        }
    }
    cout<<max_length(s,0,n-1)<<"\n";
    cout<<max_length_linearDP(s,n)<<"\n";
    return 0; 
}