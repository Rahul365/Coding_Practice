#include<bits/stdc++.h>
using namespace std;

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
        memo = vector<vector<int>>(n+1,vector<int>(m+1,-1));
        return match(s,p,n,m);
    }
};