#include<bits/stdc++.h>
using namespace std;
/**
 * Given a list of non-negative numbers and a target integer k,
 * write a function to check if the array has a continuous subarray
 * of size at least 2 that sums up to a multiple of k, that is, sums up to n*k where n is also an integer.
*/
class Solution {
public:
   
    bool check(vector<int>& a,int i,int n,int k,int sum,int cnt){
       if(n == i){
           if(cnt > 1){
               if(k == 0 && sum!=0) return false;
               if(k >= 0 && sum==0) return true;
               if(k!=0 && sum>=0) return sum%k==0;
           }
           return false;
       }
       
        // cout<<sum<<"\n";
        // cout<<i<<" "<<n<<"\n";
       if(cnt > 1){
               if(k >= 0 && sum==0) return true;
               if(k!=0 && sum>=0 && sum%k==0) return true; 
        }
        
       if(check(a,i+1,n,k,sum+a[i],cnt+1))
       {
           return true;
       }
           return  check(a,i+1,n,k,a[i],1);
    }
    
    bool checkSubarraySum(vector<int>& a, int k) {
        int  n = a.size();
        if(n < 2){
            return false;
        }
       
        int dp[n+1];
        dp[0] = 0;
        for(int i = 1;i<=n;i++){
            dp[i] = dp[i-1] + a[i-1];
        }
        
        for(int i = 1;i<n;i++){
            for(int j = n;j>=i+1;j--){
                int sum = dp[j] - dp[i-1];
                if((k >= 0 && sum == 0) || (k!=0 && sum>=0 && sum%k == 0)){
                    return true;
                }
            }
        }
        return false;
       // return check(a,0,n,k,0,0);
    }
};