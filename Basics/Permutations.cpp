#include<bits/stdc++.h>
using namespace std;


void print(int *a,int n){
    for(int i = 0;i<n;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}
/**
 * search for first value in array a[] in range [e,s] (e>=s) which is greater than given key
*/
int search(int *a,int key,int s,int e){
    while(e >= s){
        if(a[e] > key){
            return e;
        }
        --e;
    } 
    return s;
}

void reverse(int *a,int s,int e){
    while(s < e){
        swap(a[s],a[e]);
        s++,e--;
    }
}

bool permute(int *a,int n){
    bool nextpermutation = false;
    for(int i = n-2;i>=0;i--){
        if(a[i] < a[i+1]){//look for index i for which preceding value is greater than
            int id = search(a,a[i],i+1,n-1);//look for element > a[i] from n-1 to i+1
            swap(a[id],a[i]);//swap current element with a[id] : id->element found in the previous step
            reverse(a,i+1,n-1);//reverse the subarray from i+1 to n-1
            nextpermutation = true;//flip the flag
            break;
        }
    }

    return nextpermutation;
}

int main(){
    int a[] = {1,2,3};
    int n = sizeof(a)/sizeof(a[0]);

    do{
        print(a,n);
    }while(permute(a,n));
    return 0;
}