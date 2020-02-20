#include<bits/stdc++.h>
using namespace std;

/**
 * Given an array of size n.
 * And some queries of form (l,r,k) such that we have to add number k to all the elements ranging from l to r
 * in the array.
 * After each query is processed, print the final array.
 * 
 * 
 * Brute force :
 *  Now brute force idea is to add number k to all the elements from a[l] to  a[r]
 *  for each query
 *  this way time compleixty will be O(n^2)
 * 
 * Efficent Approach:
 * For each query do this
 * arr[l]+=k and arr[r+1] += (-k);
 * 
 * after processing each query 
 * do this 
 *  for(int i = 1;i<n;i++)
 *     arr[i] = arr[i] + arr[i-1];
*/
void print(int *arr,int n){
    for(int i = 0;i<n;i++){
        cout<<arr[i]<<" ";
    }cout<<"\n";
}

int main(){
    int arr[] = {0,0,0,0,0,0,0,0,0,0};
    int n = sizeof(arr)/sizeof(arr[0]);

    int l,r,k;
    int q = 4;//queries;
    while(q--){
        cin>>l>>r>>k;
        arr[l] += k;
        if(r+1 < n)
        arr[r+1] += (-k);
        print(arr,n);
    }

    for(int i =1;i<n;i++)
        arr[i] += arr[i-1];

    
    print(arr,n);
    return 0;
}