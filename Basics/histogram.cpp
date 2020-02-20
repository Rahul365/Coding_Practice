#include<bits/stdc++.h>
using namespace std;

/**
 * Given heights of n bars on a horizontal plane. Calculate the maxArea which can be formed by the consecutive bars in histogram.
 * if a adjacent bar has height greater than current bar then current bar can span into the bar with maximum height
*/

long long int maxAreaHistogram(long long int *a,int n){
    long long int maxArea = 0;
    stack<long long int> stk;

    for(int i =0 ;i<=n;i++){
        while(!stk.empty() && (i == n || a[stk.top()] > a[i])){
            long long int height = a[stk.top()];
            stk.pop();
            long long int width = (stk.empty()?i:i-stk.top()-1);
            maxArea = max(maxArea,height*width);
        }
        if(i<n)
            stk.push(i);
    }
    return maxArea;
}

int main(){
    long long int a[] = {1,2,3,3,5,4};
    int n = sizeof(a)/sizeof(a[0]);
    cout<<maxAreaHistogram(a,n)<<"\n";
    return 0;
}