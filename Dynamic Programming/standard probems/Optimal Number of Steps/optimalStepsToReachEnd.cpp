#include<bits/stdc++.h>
using namespace std;

/*O(n^2) solution*/
int optimalStepstoreachend(int *a,int n){
    if(n == 0 || a[0] == 0){
        return -1;
    }
    int result[n];//minimum number of jumps required to reach n-1 index
    result[0] = 0;//minimum number of steps to reach 0 is 0
    for(int i = 1;i<n;i++){
        result[i] = INT_MAX;
        for(int j = 0; j<i;j++){
            if(j + a[j] >= i && result[j]+1 < result[i]){
                result[i] = result[j] + 1;
            }
        }
    }
    return result[n-1];//minimum number of steps to reach end
}


/*O(n) solution */
int minJumpsToReachEnd(int *a,int n){
    if(n == 0 || a[0] == 0) return -1;//if there are 0 elements or jump value at initial index if 0 , then we can't jump any further
    if(n < 2) return 0; // if there is only one element
    //base cases handled above
    int ans = 1;//minimum jumps required is 1 
    int limit = a[0];//0...a[0] -> initial jump range
    int maxJump = 0;//maximum jump that can be made within this range
    for(int i = 1;i<n;i++){
        if(i > limit){//if i is greater than current jump range
            ans++;//count  the jump
            limit = maxJump;//update the new limit
        }
        maxJump = max(maxJump,i + a[i]);//update maxjump length at each index in order to make max Jump possible when limit gets exhausted
    }

    return ans;
}

int main(){
    int arr[] = {2,3,1,1,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<optimalStepstoreachend(arr,n)<<"\n";
    cout<<minJumpsToReachEnd(arr,n)<<"\n";
    return 0;
}