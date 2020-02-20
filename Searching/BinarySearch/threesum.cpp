/**
 * Given an array of +ve and -ve integers. Find all such pairs of three numbers a,b,c
 * such that a + b + c == 0
 * 
 * 
*/
#include<bits/stdc++.h>
using namespace std;


void merge(int *a,int l,int m,int r){
    int i = l;
    int j = m+1;
    int N = r-l+1;
    int c[N];
    int k = 0;
    while(i <= m && j <= r){
        while(i <= m && a[i] <= a[j]){
            c[k++] = a[i++];
        }
        while(j <= r && a[j] < a[i]){
            c[k++] = a[j++];
        }
    }
    while(i <= m){
        c[k++] = a[i++];
    }
    while(j <= r){
        c[k++] = a[j++];
    }
    k = l;
    for(int i = 0;i<N;i++)
        a[k++] = c[i];
}

void mergesort(int *a,int l,int r){
    if(l < r){
        int mid = l + (r-l)/2;
        mergesort(a,l,mid);
        mergesort(a,mid+1,r);
        merge(a,l,mid,r);
    }
}

vector<vector<int>> threesums(int *a,int n){
  mergesort(a,0,n-1);//sort the array
  vector<vector<int>> result;
    for(int i = 0;i<n-3;i++){
        while(i > 0 && a[i-1] == a[i]){
            i++;
        }
        int l = i+1;
        int r = n-1;
        while(l < r){
            int sum = a[i] + a[l] + a[r];
            if(sum == 0){
                result.push_back({a[i],a[l],a[r]});
                l++;
                r--;
            }
            else if(sum < 0){
                int cl = l;
                while(l < r && a[cl] == a[l]) l++;
            }
            else{
                int cr = r;
                while(l < r && a[cr] == a[r]) r--;
            }
        }
    }
    return result;
}

int main(){
    int arr[] = {-1,0,1,2,-1,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<"Unsorted : ";
    for(int i = 0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\nSorted : ";
    vector<vector<int>> result = threesums(arr,n);
     for(int i = 0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
    for(vector<int> v : result){
        cout<<"{"<<v[0]<<","<<v[1]<<","<<v[2]<<"}\n";
    }
    return 0;
}