#include<bits/stdc++.h>
using namespace std;

int memo[1000][1000];
int countOccurences(string s,string t,int n,int m){
    if(n == 0)
        return 1;
    if(m == 0)
        return 0;
    
    
    int &ans = memo[n][m];

    if(ans!=-1)
        return ans;

    if(s[n-1] == t[m-1]){
        ans = countOccurences(s,t,n-1,m-1)//move both target string index as well as source string index to look for further match
         + countOccurences(s,t,n,m-1); // move the source string index to look for another character that matches nth character
    }
    else
        ans = countOccurences(s,t,n,m-1);

    return ans;
}

/**
 * S->target string to look for
 * T->Source string 
 * n->length of target
 * m->length of source
 */
int countOccurencesLinear(string s,string t,int n,int m){
    if(n > m)//s can't appear as subsequenc in t
        return 0;
    int dp[n+1][m+1];
    //dp[i][j] = gives the number of times i characters of string 's' appears in 't'
    for(int i = 1;i<=n;i++){
        dp[i][0] = 0;//you can't search for a subsequence in 0 lenght source string
    }

    for(int i = 0;i<=m;i++){
        dp[0][i] = 1;//only one to find an empty string in source
    }

    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(s[i-1] == t[j-1]){
                dp[i][j] = dp[i-1][j-1]  + dp[i][j-1];
            }
            else{
                dp[i][j] = dp[i][j-1];
            }
        }
    }

    return dp[n][m];
}

int main(){
    string s = "ge";
    string t = "geeksforgeeks";
    int n = s.length();
    int m = t.length();
    for(int i = 0;i<=n;i++){
        for(int j = 0;j<=m;j++){
            memo[i][j] = -1;
        }
    }

    cout<<countOccurences(s,t,n,m)<<"\n";
    cout<<countOccurencesLinear(s,t,n,m)<<"\n";
    return 0;
}