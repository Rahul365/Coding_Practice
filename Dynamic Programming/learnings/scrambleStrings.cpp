#include<bits/stdc++.h>
using namespace std;
/**
 * https://leetcode.com/problems/scramble-string/
*/
class Solution {
public:
    map<pair<string,string>,int> dp;
    
    bool check(string a,string b){
        const int n = a.length();
        const int m = b.length();
        if(dp.find({a,b})!=dp.end())
            return dp[{a,b}];
        int &ans = dp[{a,b}];
        if(n!=m) return false;
        if(m == n && n==1){
            return ans = a[0] == b[0];
        }
        for(int i = 1;i<n;++i){
            if(check(a.substr(0,i),b.substr(0,i)) && check(a.substr(i),b.substr(i)))
                return ans = true;
            if(check(a.substr(0,i),b.substr(n-i)) && check(a.substr(i),b.substr(0,n-i)))
                return ans = true;
        }
        return false;
    }
    
    bool isScramble(string s1, string s2) {
        dp.clear();
        if(s1.length()!=s2.length())
            return false;
        return check(s1,s2);
    }
};