#include<bits/stdc++.h>
using namespace std;
/**
 * Given an array of positive and negative integers. Find max sum consecutive subarray sum.
 * 
 * 
*/

int kadanealgo(int *a,int n){
    int maxsum = -1;
    int maxsofar = 0;
    for(int i = 0;i<n;i++){
        maxsofar += a[i];
        if(maxsofar < 0){
            maxsofar = 0;
        }
        else if(maxsofar > maxsum){
            maxsum = maxsofar;
        }
    }

    if(maxsum == -1){//case when all the elements are negative
        maxsum = a[0];
        for(int i = 1;i<n;i++){
            if(a[i] > maxsum){
                maxsum = a[i];
            }
        }
    }
    return maxsum;
}

int main(){
    int arr[] = {-1,2,3,-2,1,2,0,-4};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<kadanealgo(arr,n)<<"\n";
    return 0;
}