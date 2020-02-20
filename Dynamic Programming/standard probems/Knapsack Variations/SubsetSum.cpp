#include<bits/stdc++.h>
using namespace std;

/**
 * Given an array of n numbers. Give an algorithm to check whether there exists a subset with given sum T.(need not be contiguos one)
 * eg A[] = {3,4,5,6,2,17,3}
 * T = 17
 * Yes, there exists subset with the given sum
 * 4 + 5 + 6 + 2 = 17
 * 3 + 5 + 6 + 3 = 17
 */

bool subsetSum(int *A,int n,int T){
    bool dp[n+1][T+1];
    
    for(int i = 1;i<=T;i++){
        dp[0][i] = 0;//if number of items are zero, then non-zero sum is not posssible
    }
    for(int i  = 0;i<=n;i++){
        dp[i][0] = true;//zero sum is possible with any number of items (i.e. by not adding any number of items)
    }

    
    for(int i = 1;i<=n;i++){//number of items
        for(int C = 1;C<=T;C++){//capacity to fill using i number of items
            dp[i][C] = dp[i-1][C];
            if(C >= A[i-1]){
                dp[i][C] |= dp[i-1][C-A[i-1]];
            }
        }
    }

    return dp[n][T];
}

/*Space optimized approach*/
bool subsetSumII(int *A,int n,int T){
    bool dp[2][T+1];
    

    for(int i = 0;i<=n;i++){
        for(int j = 0;j<=T;j++){
                if(j == 0){
                    dp[i%2][j] = true;
                }
                else if(i == 0){
                    dp[i%2][j] = false;
                }
                else{
                    dp[i%2][j] = dp[(i+1)%2][j];
                    if(j >= A[i-1]){
                        dp[i%2][j] |= dp[(i+1)%2][j-A[i-1]];
                    }
                }
        }
    }

    return dp[n%2][T];
}

int main(){
    int a[] = {3,2,4,19,3,7,13,10,6,11};
    int n = sizeof(a)/sizeof(a[0]);
    int T = 17;
    cout<<"Check : "<<subsetSumII(a,n,T)<<"\n";
    return 0;
}