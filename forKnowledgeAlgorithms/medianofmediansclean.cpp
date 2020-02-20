#include<bits/stdc++.h>
using namespace std;

int findmedian(int arr[],int n){
    sort(arr,arr+n);
    return arr[n/2];
}

int partition(int arr[],int l,int r,int key){
    int i = l;
    while(i < r && arr[i]!=key) ++i;
    swap(arr[i],arr[l]);
    
    i = l+1;
    int j = r;
    while(i <= j){
       
        while(i <= j && arr[i] <= key){
            i++;
        }
        while(i <= j && arr[j] > key){
            --j;
        }
        if(i<j) swap(arr[i],arr[j]);
    }
    swap(arr[l],arr[j]);
    return j;
}

int kthsmallest(int arr[],int l,int r,int k){
    if(l > r || r-l+1 < k) return INT_MAX;
    int n = r-l+1;
    int N = n/5 + (n%5!=0);
    int median[N];//store the median of each group

    for(int i = 0;i<N;i++){
        median[i] = findmedian(arr+l+i*5,(i==N-1)?n%5:5);
    }
    
    int medianofmedian = (N == 1)?median[N-1]:kthsmallest(median,0,N-1,N/2);
    
    int pivotindex = partition(arr,l,r,medianofmedian);
    
    if(pivotindex - l > k-1) return kthsmallest(arr,l,pivotindex-1,k);
    else if(pivotindex-l < k-1) return kthsmallest(arr,pivotindex+1,r,k-pivotindex+l-1);
    return arr[pivotindex];
}

int main(){
    int arr[] = {15,3,4,2,2,23,22,3};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<kthsmallest(arr,0,n-1,6)<<"\n";
    sort(arr,arr+n);
    for(int i = 0;i<n;i++) cout<<arr[i]<<" ";
    cout<<"\n";
    return 0;
}