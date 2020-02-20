#include<bits/stdc++.h>
using namespace std;

/**
 * Given an unsorted array of nonnegative integers, find a continuous subarray which adds to a given number.
 * 
 */ 
pair<int,int> contiguosSubarraySum(int *a,int s,int n){
    int sum = 0;
    int x = 0;
    int y = 0;
    while(y<n){
        sum += a[y];
        while(sum > s){//loop until sum !> s to maintain subarray window
            sum-=a[x++];
        }
        //now compare the sum value with given s
        if(sum == s){
            break;
        }
        y++;
    }
    if(sum == s)
        return {x+1,y+1};
    return {-1,-1};
}

int main(){
    int a[] = {1,4,20,3,10,5};
    int n = sizeof(a)/sizeof(a[0]);
    int s = 33;
    pair<int,int> p = contiguosSubarraySum(a,s,n);

    cout<<p.first<<" "<<p.second<<"\n";
    
    return 0;
}