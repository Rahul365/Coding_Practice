#include<bits/stdc++.h>
using namespace std;

vector<int> binarysearch(int *a,int n,int key){
    vector<int> ans(3,-1);//{lowerboundIndex,elementIndex,upperboundIndex}
    int l = 0;
    int r = n-1;
    while(l <= r){
        int mid = l + (r-l)/2;
        if(a[mid] == key)
        {
            ans[1] = mid;
            break;
        }
        else if(a[mid] < key){
            ans[0] = mid;
            l = mid+1;
        }
        else{
            ans[2] = mid;
            r = mid-1;
        }
    }
    return ans;
}

int main(){
    int a[] = {1,2,3,4,5,7,10,11,12};
    int n = sizeof(a)/sizeof(a[0]);

    int key = 100;
    vector<int> find = binarysearch(a,n,key);
    cout<<"left(lowerbound) : "<<(find[0]!=-1?a[find[0]]:-1)<<"\n";
    cout<<"key pos : "<<(find[1]!=-1?a[find[1]]:-1)<<"\n";
    cout<<"right(upperbound) : "<<(find[2]!=-1?a[find[2]]:-1)<<"\n";
    return 0;
}