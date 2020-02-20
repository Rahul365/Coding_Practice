#include<bits/stdc++.h>
using namespace std;

int knapsack01(int C,int n,int *s,int *v){
    int M[n+1][C+1];
    //fill the knapsack with capacity 0 with value 0
    for(int i=0;i<=n;i++)
            M[i][0] = 0;
    for(int k = 0;k<=C;k++)
            M[0][k] = 0;
    
    for(int i= 1;i<=n;i++){
        for(int k = 1;k<=C;k++){
        
                M[i][k] = M[i-1][k];//ith item not included in the knapsack of capacity k
                if(k - s[i-1] >= 0){
                    //include and compare the ith item
                    M[i][k] = max(M[i][k],M[i-1][k-s[i-1]]+v[i-1]);
                }
            // cout<<M[i][k]<<" ";
        }
        // cout<<"\n";
    }

    int maxVal = 0;
    //now Max value can be checked for n items for Capacity K => [1,C]
    for(int k = 1;k<=C;k++){
        maxVal = max(maxVal,M[n][k]);
    }

    return maxVal;
}


int main(){
    int s[] = {1,4,2};//size of n items
    int v[] = {50,40,60};//value of n items
    int n = sizeof(s)/sizeof(s[0]);//number of items
    int C = 5;//knapsack capacity
    cout<<knapsack01(C,n,s,v)<<"\n";
    return 0;
}