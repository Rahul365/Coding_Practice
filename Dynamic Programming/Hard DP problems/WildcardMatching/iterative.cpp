#include<vector>
#include<string>
using namespace std;
/**
 * https://leetcode.com/problems/wildcard-matching/
*/
class Solution {
public:
    vector<vector<int>> memo;
    bool match(const string &a,const string &b,int n,int m){
        int &ans = memo[n][m];
        if(ans!=-1)
            return ans;
        ans = 0;
        if(n == 0)
        {
            while(m!=0)
            {    if(b[m-1]!='*')
                    return false;
                 --m;
            }
            ans = 1;
            return true;
        }
        if(m == 0)
            return false;
        bool curr_match = a[n-1] == b[m-1] || b[m-1]=='*' || b[m-1] == '?';
        if(curr_match){
            return ans = match(a,b,n-1,m-1) 
                || (b[m-1]=='*'?match(a,b,n-1,m)||match(a,b,n,m-1):false);
        }
        return false;
    }
    
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        // memo = vector<vector<int>>(n+1,vector<int>(m+1,-1));
        // return match(s,p,n,m);
        vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
        //dp[i][j] => tells whether the string s[0...i] matches the pattern p[0....j]
        dp[0][0] = true;
        for(int j = 1;j<=m && p[j-1]=='*';++j){
            dp[0][j] = true;
        }
        for(int i = 1;i <= n;++i){
            for(int j = 1;j <= m;++j){
                bool curr_match = (s[i-1] == p[j-1] || p[j-1] == '?' || p[j-1] == '*')?true:false;
                if(curr_match){
                    dp[i][j] = dp[i-1][j-1] || (p[j-1]=='*'?dp[i-1][j]|dp[i][j-1]:false);
                }
                else{
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }
};