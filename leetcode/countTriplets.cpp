#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;
const int N = 1e6+1;
/*
    Given array of distinct integers.Find the number of triplets such that sum of two elements in array == third element in the array.
    i.e A[i] + A[j] == A[k]
    Algo solveII():
    1)sort the given array
    2)count = 0
    3)for(each i = n-1 to i>1)
        set two pointers  l = 0; r = i-1;
        while( l < r){
            sum = a[l] + a[r];
            if(sum == a[i])
            {
                    count++;
                    l++;
                    r--;
            }
            else if(sum > a[i])
                r--;
            else
                l++;
        }
    4)return (count == 0)?-1:count;
*/
void solveI(){
        int n;
        cin>>n;
        int a[n];
        unordered_map<int,bool> table;
        for(int i = 0;i<n;i++){
            cin>>a[i];
            table[a[i]] = true;
        }
        sort(a,a+n);
        int maxval = a[n-1];
        int count = 0;
        for(int i= 0;i<n-1;i++){
            int l = i;
            int r = i+1;
            while(l<n && r<n){
                if(a[l]+a[r] > maxval)
                    break;
                if(table[a[l] + a[r]]){ 
                    count++;
                }
                r++;
            }
        }
       
        
        cout<<(count==0?-1:count)<<"\n";    
}

void solveII(){
    int n;
    cin>>n;
    int a[n];
    for(int i = 0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int count = 0;
    for(int i=n-1;i>=0;i--){
        int l = 0;
        int r = i-1;
        while(l<r){
            if(a[l] + a[r] == a[i]){
                count++;
                l++;r--;
            }
            else if(a[l] + a[r] < a[i]){
                l++;
            }
            else{
                r--;
            }
        }
    }
    cout<<(count==0?-1:count)<<"\n";
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        solveII();
    }
	return 0;
}