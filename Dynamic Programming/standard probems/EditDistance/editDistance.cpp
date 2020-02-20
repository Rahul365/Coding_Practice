#include<bits/stdc++.h>
using namespace std;

/**
 * Given two strings of length m and n.
 * Transform string A to B using following operations:
 *  1)Delete a element from A 
 *  2)Insert a element into A
 *  3)Replace an element in A 
 * Give an algorithm to find the minimum number of operations needed to convert A to B
 */

int dp[1000][1000];
//memoization DP
int num_operations(string A,string B,int m,int n){
    if(m == 0)//if no characters left in A then must insert new characters
        return n;
    if(n == 0)//if A's length is more than B then must delete characters from A
        return m;
    
    int &ans = dp[m][n];

    if(ans != -1)
        return ans;
    if(A[m-1] == B[n-1]){
        ans = num_operations(A,B,m-1,n-1);
    }
    else{
        ans = 1 + min(
            num_operations(A,B,m-1,n-1)//replace
            ,min(num_operations(A,B,m-1,n)//delete
            ,num_operations(A,B,m,n-1)//insert
            )
        );
    }
    return ans;
}

int num_operations_iterative(string A,string B,int m,int n){
    int dp[m+1][n+1];

    for(int i = 0;i<=m;i++){
        for(int j = 0;j<=n;j++){
            if(i == 0){
                dp[i][j] = j;
            }
            else if(j == 0){
                dp[i][j] = i;
            }
            else if(A[i-1] == B[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1 + min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));
            }
        }
    }

    return dp[m][n];
}

int num_operations_rec(string A,string B,int m,int n){
    cout<<m<<" "<<n<<"\n";
    if(n==0)
        return m;
    if(m==0)
        return n;

    if(A[m-1] == B[n-1]){
        return num_operations_rec(A,B,m-1,n-1);
    }
    else
       return 1 + min(num_operations_rec(A,B,m-1,n-1),min(num_operations_rec(A,B,m-1,n),num_operations_rec(A,B,m,n-1)));
}

int main(){
    string B = "uytdlcgdewhtaciohordtqkvwcsgspqoqmsboaguwnny";
    string A = "zvfrkmlnozjkpqpxrjxkitzyxacbhhkicqcoendtomfgdwdwfcgpxiqvk";
    //ANS : 50
    for(int i = 0;i<=A.length();i++)
        for(int j = 0;j<=B.length();j++){
            dp[i][j] = -1;
        }
    
    cout<<num_operations(A,B,A.length(),B.length())<<"\n";
    cout<<num_operations_iterative(A,B,A.length(),B.length())<<"\n";
    // cout<<num_operations_rec(A,B,A.length(),B.length())<<"\n"; //Give TLE for given input
    return 0;
}