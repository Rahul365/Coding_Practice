#include<bits/stdc++.h>
using namespace std;


void merge(int *a,int l,int mid,int r){
    int len = r-l + 1;
    int c[len];
    int k = 0;
    int i = l;
    int j = mid+1;
    while(i <= mid && j <= r){
         while(i<=mid && a[i] <= a[j]){
             c[k++] = a[i++];
         }

         while(j<=r && a[i] > a[j]){
             c[k++] = a[j++];
         }
    }

    while(i<=mid){
        c[k++] = a[i++];
    }

    while(j<=r){
        c[k++] = a[j++];
    }
    
    k = l;
    for(int i = 0;i<len;i++){
        a[k++] = c[i];
    }
}

void mergesort(int *a,int l,int r){
    if(l < r){
        int mid = l + (r-l)/2;
        mergesort(a,l,mid);
        mergesort(a,mid+1,r);
        merge(a,l,mid,r);
    }
}

int main(){
    int a[] = {-1,0,1,2,-1,4};
    int n = sizeof(a)/sizeof(a[0]);
    mergesort(a,0,n-1);
    for(int i = 0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}