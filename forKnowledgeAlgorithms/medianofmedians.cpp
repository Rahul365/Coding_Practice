#include<bits/stdc++.h>
using namespace std;

int findmedian(int arr[],int n){
    //here n <= 5
    sort(arr,arr+n);//sort the group of n elements
    return arr[n/2];//return the middle element
}


int partition(int arr[],int l,int r,int key){
    int i;
    //find key index
    for(i = l;i<r && arr[i]!=key;i++);
    swap(arr[i],arr[r]);
    //standard quicksort partition procedure
    i = l;
    for(int j = l;j<r;j++){
        if(arr[j] <= key){
            swap(arr[j],arr[i]);
            ++i;
        }
    }
    swap(arr[i],arr[r]);
    return i;
}


int kthsmallestnumber(int arr[],int l,int r,int k){
    if(k < 0 || k > r-l+1) return INT_MAX;//return dummy value
    int n = r-l+1;//number of elements in the range arr[l..r]

    //divide array into n/5 groups of length 5 each
    //sort each group and store their medium
    int N = (n+4)/5; //number of groups for given arr of length n
    //e.g n = 15 , N = 3
    //n = 16 , N = 4 (last group to store the last element)
    int median[N];
    int i;
    for(i = 0;i<n/5;i++){
        median[i] = findmedian(arr + l + i*5,5); //arr+l+i*5 = &arr[l+i*5]
    }
    if(i*5 < n){
        //last group with less than 5 elements
        median[i] = findmedian(arr + l + i*5,n%5);
        //n%5 = remaining number of elements in the given arr[]
        ++i;
    }

    int medianOfmedian = (i==1)?median[i-1]:kthsmallestnumber(median,0,i-1,i/2);

    int pivotindex = partition(arr,l,r,medianOfmedian);

    if(pivotindex-l == k-1){
         return arr[pivotindex];
    }
    else if(pivotindex-l > k-1){
        return kthsmallestnumber(arr,l,pivotindex-1,k);
    }
    return kthsmallestnumber(arr,pivotindex+1,r,k-pivotindex+l-1);
}



void shuffle(int *arr,int n){
    srand(time(NULL));
    for(int i = n-1;i>=0;i--){
        swap(arr[i],arr[rand()%(i+1)]);
    }
}

int main(){
    int n = 19;
    int arr[n];
    for(int i = 0;i<n;i++){
        arr[i] = i+1;
    }
    shuffle(arr,n);
    for(int i = 0;i<n;i++){
        cout<<arr[i]<<" ";
    }cout<<"\n";
    int k = 10;//return the 10th smallest element in the unsorted array
    
    cout<<kthsmallestnumber(arr,0,n-1,k)<<"\n";
    return 0;
}