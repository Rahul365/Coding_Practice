#include<bits/stdc++.h>
using namespace std;

/*
 * Given an array of integers of length n-1;
 * The elements in the array are in the range of 1 to n
 * One number of is missing in the array for this range.
 * Find and print that missing number
 **/
int findmissingnum(int *a,int size){
    int n = size + 1;
    int missing_num = 0;

    for(int i = 1;i<=n;i++){
        missing_num ^= i;
    }

    for(int i = 0;i<size;i++){
        missing_num ^= a[i];
    }

    return missing_num;
}

int main(){
    int a[] = {5,2,3,6,1};
    int size = sizeof(a)/sizeof(a[0]);
    cout<<findmissingnum(a,size)<<"\n";
    return 0;
}