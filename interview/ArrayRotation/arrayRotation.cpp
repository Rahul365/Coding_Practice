#include<bits/stdc++.h>
using namespace std;
/*Left rotate Array by d elements */
void leftrotateOneByOne(int *arr,int n){
    int temp = arr[0];
    for(int i = 0;i<n-1;i++){
        arr[i] = arr[i+1];
    }
    arr[n-1] = temp;
}

void leftrotate(int *arr,int d,int n){
    for(int i = 0;i<d;i++){
        leftrotateOneByOne(arr,n);
    }
}
//O(n*d) time
//O(1) space
/*-------------------------------*/

int gcd(int a,int b){
    if(b == 0) return a;
    return gcd(b,a%b);
}

void leftrotateII(int *a,int d,int n){
    int GCD = gcd(n,d);
    for(int i = 0;i<GCD;i++){
        int j = i;
        int temp = a[i];
        while(1){
            int k  = j+d;
            if(k >= n){
                k-=n;
            }
            if(k == i)
                break;
            a[j] = a[k];
            j = k;
        }

        a[j] = temp;
    }
}

void reverse(int *a,int l,int r){
    while(l<r){
        swap(a[l++],a[r--]);
    }
}

void easySolve(int *a,int d,int n){
    if(n < d) d = d-n;
    reverse(a,0,d-1);
    reverse(a,d,n-1);
    reverse(a,0,n-1);
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        int n,l;
        cin>>n>>l;
        int a[n];
        for(int i = 0;i<n;i++)
            cin>>a[i];

        // leftrotate(a,l,n);
        easySolve(a,l,n);
        
        //Note :  to do the right the rotation left rotate the array by length (n-l)
        for(int i = 0;i<n;i++){
            cout<<a[i]<<" ";
        }cout<<"\n";
    }
    return 0;
}