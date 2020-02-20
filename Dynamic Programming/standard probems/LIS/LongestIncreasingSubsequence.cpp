#include<bits/stdc++.h>
using namespace std;
/* a1 < a2 < a3 < ..... < ak*/
int longestIncreasingSubsequence(int *a,int n){
    int lis[n];
    lis[0] = 1;
    int ans = 1;
    for(int i = 1;i<n;i++)
    {
        lis[i] = 1;
        for(int j= 0;j<i;j++){
                if(a[i] > a[j] && lis[i] < 1 + lis[j]){
                    lis[i] = 1 + lis[j];
                }
        }
        ans = max(ans,lis[i]);
    }

    return ans;
}

/*a1 > a2 > a3 >......>ak*/
int longestDecreasingSubsequence(int *a,int n){
    int lds[n];
    lds[0] = 1;
    int ans = 0;
    for(int i  = 1;i<n;i++){
        lds[i] = 1;
        for(int j = 0;j<i;j++){
            if(a[i] < a[j] && lds[i] < 1+lds[j]){
                lds[i] = 1  + lds[j];
            }
        }
        ans = max(ans,lds[i]);
    }
    return ans;
}

int main(){
    int a[] = {5,5,5,1,2,4,2,3,4,5,6};
    int n = sizeof(a)/sizeof(a[0]);
    cout<<longestIncreasingSubsequence(a,n)<<"\n";
    cout<<longestDecreasingSubsequence(a,n)<<"\n";
    return 0;
}