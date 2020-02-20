#include<bits/stdc++.h>
#define seed  srand(time(NULL))

using namespace std;


int pow(int x,int y){
    int r =1;
    while(y){
        if(y&1) r*=x;
        x = x*x;
        y>>=1;
    }
    return r;
} 

bool sorted(int arr[],int n){
    for(int i=1 ;i<n;i++) if(arr[i-1] > arr[i]) return false;
    return true;
}

void reverse(int arr[],int n){
     int i = 0;
     int j = n;
     while(i < j) swap(arr[i],arr[j]),++i,--j;   
}

void prefixSortUsingRandom(int arr[],int n){
    while(!sorted(arr,n)){
        int index = rand()%n;
        reverse(arr,index);
    }
}

void prefixSort(int arr[],int n){
    //find the index of max element
    //reverse arr[0..index]
    //reverse arr[0..n-1]
    
    int s = n;
    while(s > 1){
        int maxindex = s-1;
        for(int i= 0;i<=s-1;i++){
            if(arr[maxindex] < arr[i]){
                maxindex = i;
            }
        }
        //find the index of max element in arr[0..s-1]
        //then reverse the arr from 0 to maxindex
        reverse(arr,maxindex);//after this max element is at the front of the array
        reverse(arr,s-1);//now reverse the array from 0 to s-1
        //so that the max element is position at the end here
        //now reduce the number of elements to sort by 1
        --s;
    }
}

int main(){
    seed;
    int arr[] = {3,23,1,1,12,1,224,435,34,5234,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    prefixSort(arr,n);
    for(int i =0;i<n;i++) cout<<arr[i]<<" ";
    cout<<"\n";
    return 0;
}