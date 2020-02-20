#include<bits/stdc++.h>
using namespace std;

int partition(int *a,int l,int r){
    int piv = a[l];
    int i = l+1;
    int j = r;
    while(i<=j){
        while(a[i]<=piv){
            i++;
        }
        
        while(a[j] > piv){
            j--;
        }

        if(i < j){
            swap(a[i],a[j]);
        }
    }
    swap(a[l],a[j]);
    return j;
}

void quicksort(int *a,int l,int r){
    if(l <= r){
        int pid = partition(a,l,r);
        quicksort(a,l,pid-1);
        quicksort(a,pid+1,r);
    }
}

int main(){
    int a[] = {10,9,8,7,6,5,4,3,2,1};
    int n = sizeof(a)/sizeof(a[0]);
    quicksort(a,0,n-1);
    for(int i = 0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}