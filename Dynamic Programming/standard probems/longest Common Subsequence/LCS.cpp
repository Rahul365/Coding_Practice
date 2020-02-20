#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;
/**
 * Given two strings in lowercase,
 * find the longest string whose permutations are subsequence of given two strings.
 * The output longest string must be sorted.
 * 
*/
string memo[1000][1000];
string LCS(string A,string B,int n,int m){
    if(n == 0 || m == 0)
        return "";
    string &ans = memo[n][m];
    if(ans != "0")
        return ans;
    ans = "";
    if(A[n-1] == B[m-1]){
        ans = LCS(A,B,n-1,m-1) + A[n-1];
    }
    else{
        string a = LCS(A,B,n,m-1);
        string b = LCS(A,B,n-1,m);
        ans = a.length() > b.length()?a:b;
    }
    return ans;
}

string LCSiterative(string A,string B,int n,int m){
    string dp[n+1][m+1];
    for(int i = 0;i<=m;i++){
        dp[0][i] = "";
    }
    for(int j = 0;j<=n;j++){
        dp[j][0] = "";
    }
    
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(A[i-1] == B[j-1]){
                dp[i][j] = dp[i-1][j-1] + A[i-1];
            }
            else{
                int a = dp[i][j-1].length();
                int b = dp[i-1][j].length();
                dp[i][j] = a>b?dp[i][j-1]:dp[i-1][j];
            }
        }
    }
    return dp[n][m];
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        string s1,s2;
        cin>>s1;
        cin>>s2;
        sort(s1.begin(),s1.end());
        sort(s2.begin(),s2.end());
        for(int i = 0;i<=n;i++)
            for(int j = 0;j<=m;j++)
                memo[i][j] = "0";
        //Now to find the longest common subsequence of the two strings
        cout<<LCSiterative(s1,s2,n,m)<<"\n";
    }
	return 0;
}