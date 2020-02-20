#include<bits/stdc++.h>
using namespace std;
/**
 * Algorithm paradigm : Incremental approach
 * Worst case : O(n^2)
 * space : O(1)
 * stable : Yes
 * Online : Yes
*/

void insert(int *arr,int index){
    int key = arr[index];
    int j = index-1;
    while(j>=0 && arr[j] > key){
        arr[j+1] = arr[j];
        --j;
    }
    arr[j+1] = key;
}

void insertionsort(int *arr,int n){
    for(int i= 1;i<n;i++){
        insert(arr,i);
    }
}

void insertionsortdesc(int arr[],int n){
    for(int i = 1;i<n;i++){
        int j = i-1;
        int key = arr[i];
        //insert key at it's correct position
        while(j >=0 && arr[j] > key){
            //in range j = (i-1)...0
            //if any element is greater than key
            //then shift that element by one position to right
            //i.e if(a[3] > key) a[4] = a[3] now index j = 3-1 = 2
            //then come out of loop 
            //now put the key at position j+1
            //a[j+1] = key;
            arr[j+1] = arr[j];//arr[3] = arr[2]
            --j;
        }
        arr[j+1] = key;
 
    }
}
int main(){
    int arr[] = {5,4,3,2,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionsort(arr,n);
    for(int v : arr){
        cout<<v<<" ";
    }
    cout<<"\n";
    return 0;
}