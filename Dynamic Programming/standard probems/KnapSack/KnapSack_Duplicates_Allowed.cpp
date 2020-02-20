#include<bits/stdc++.h>
using namespace std;

/*
    Calculate the max profit value for given KnapSack capcity if duplicates are allowed
*/
int getMaxValue(int C,int n,int *s,int *v){  
    int M[C+1];
    M[0] = 0;//0 value for filling knapsack capacity of 0
    for(int i = 1;i<=C;i++){
        M[i] = M[i-1];
        for(int j = 0;j<n;j++){
            if(i >= s[j])
                M[i] = max(M[i],M[i-s[j]]+v[j]);
        }
    }
    return M[C];
}

int main(){
    int s[] = {1,4,2};//size of n items
    int v[] = {50,40,60};//value of n items
    int n = sizeof(s)/sizeof(s[0]);//number of items
    int C = 5;//knapsack capacity
    cout<<getMaxValue(C,n,s,v)<<"\n";
    return 0;
}