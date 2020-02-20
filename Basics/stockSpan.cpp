#include<bits/stdc++.h>
using namespace std;

/**
 * Find the number of consecutive elements A[j] for ith element such that A[j] <= A[i] && j < i
 */

int *stockSpan(int *a,int n){
    int *span = new int[n];
    span[0] = 1;//span for day 1 is always 1
    stack<int> s;
    s.push(0);
    for(int i = 1;i<n;i++){
        span[i] = 1;
        while(!s.empty() && a[s.top()] <= a[i]){
            span[i]+=span[s.top()];
            s.pop();
        }
        s.push(i);
    }
    return span;
}

int main(){
    int a[] = {30,24,12,54,32,12,11,50,60,70};
    int n = sizeof(a)/sizeof(a[0]);
    int *spans = stockSpan(a,n);
    for(int i = 0;i<n;i++){
        cout<<spans[i]<<" ";
    }
    cout<<"\n";
    return 0;
}