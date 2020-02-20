#include<bits/stdc++.h>
using namespace std;

/**
 * Problem Statement : 
 * Given that alphabets from 'A' to 'Z' are encoded in string.
 * Encoding of alphabets is as follows : 
 *  'A' = 1 
 *  'B' = 2
 *   ......
 *  'Z' = 26
 * Given string of digits. Find the total number of ways to decode the given string.
 * 
*/

/**
 * Idea : 
 * since the range of encoding is from 1 to 26.
 * so at each index we have to check for valid digit
 * and also we have to check whether we can decode a string of length 2 which falls within valid range [10,26] 
 * 
*/

/**
 * Corner Cases :
 * 1)digit at index = 0 is '0'
 * 2) digit at current index is '0' 
 * 3) digit at adjacent previous index is '0'  e.g. "0X" where  where X>='0'
 * 
*/


const int MAX = 1e5;
vector<int> memo(MAX,-1);
/**
 * Recursive Solution
*/
int num_ways_rec(string s,int n){
    if(n == 0){
        return  1;
    }

    int ways = 0;
    if(n>=1 && s[n-1] != '0'){
        ways += num_ways_rec(s,n-1);
    }

    if(n>=2){
        int num = stoi(s.substr(n-2,2));
        if(num >= 10 && num <= 26){
            ways += num_ways_rec(s,n-2);
        } 
    }
    return ways;
}

/**
 * Memoization DP Solution
*/

int num_ways_memo(string s,int n){
    if(n == 0){
        return 1;
    }

    int &ways = memo[n];
    if(ways != -1){
        return ways;
    }
    ways = s[n-1]=='0'?0:num_ways_memo(s,n-1);
    if(n >= 2){
        int num = stoi(s.substr(n-2,2));
        if(num >= 10 && num <= 26)
            ways += num_ways_memo(s,n-2);
    }
    return ways;
}

/**
 * Linear Dp solution
 * dp[0] = 1;
 * dp[1] = 1 if(s[0]!='0') else 0;
 * dp[i] = (s[i-1]!='0')?dp[i-1]:0   + (num(s[i-2],s[i-1])>=10 && num(s[i-2],s[i-1])<=26)?dp[i-2]:0;
*/
int num_ways_dp(string s,int n){
    int ways[n+1];
    memset(ways,0,sizeof(ways));
    if(n == 0 || s[0] == '0'){
        return 0;
    }
    ways[0] = 1;
    ways[1] = ways[0];
    for(int i = 2;i<=n;i++){
        int num = stoi(s.substr(i-2,2));
        ways[i] += (s[i-1] == '0')?0:ways[i-1];
        ways[i] += (num>=10 && num <= 26)?ways[i-2]:0;
    }
    return ways[n];
}

int main(){
    string s = "2266";
    int n = s.length();
    cout<<num_ways_rec(s,n)<<"\n";
    cout<<num_ways_memo(s,n)<<"\n";
    cout<<num_ways_dp(s,n)<<"\n";
    return 0;
}