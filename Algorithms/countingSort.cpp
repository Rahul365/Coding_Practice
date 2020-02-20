#include<bits/stdc++.h>
using namespace std;


void print(int *arr,int n)
{
    for(int i = 0;i<n;i++) cout<<arr[i]<<" ";
    cout<<"\n";
}

int *countingsort(int *arr,int n,int K){
    int *b = new int[n]; //sorted array
    int *c = new int[K+1]; //counting array

    for(int i = 0;i<=K;i++)
        c[i] = 0;

    for(int i = 0;i<n;i++) c[arr[i]]++;
// c[i] contains number of elements equal to i
    for(int i = 1;i<=K;i++){
        c[i]+=c[i-1];
    }
    //now c[i] contains number of elements <= i

    for(int i = 0;i<n;i++){
        b[c[arr[i]]-1] = arr[i];//put element arr[i] at position c[arr[i]-1] i.e. (at number of elements less than or equal to arr[i])
        c[arr[i]]--;
    }
    delete(c);
    return b;
}

int main(){
    srand(time(NULL));
    int MAX = rand()%100;//MAX range of elements
    int n = rand()%MAX;//number of elements in array
    int arr[n];
    cout<<"Number of elements : "<<n<<"\n";
    cout<<"MAX range : "<<MAX<<"\n";
    for(int i = 0;i<n;i++){
        arr[i] = rand()%MAX;
    }
    cout<<"Unsorted Elements of array are : ";
    print(arr,n);
    cout<<"  Sorted Elements of array are : ";
    print(countingsort(arr,n,MAX),n);
    return 0;
}