#include<bits/stdc++.h>
using namespace std;

int *slidingWindow(int *a,int n,int k){
    int *b = new int[n-k+1];
    deque<int> q;
    //process first k elements
    for(int i = 0;i<k;i++){
        while(!q.empty() && a[q.back()] <= a[i]){
            q.pop_back();
        }
        q.push_back(i);
    }
    for(int i = k;i<n;i++){
        b[i-k] = a[q.front()];
        while(!q.empty() && q.front() <= i-k){
            q.pop_front();
        }
        while(!q.empty() && a[q.back()] <= a[i]){
            q.pop_back();
        }
        q.push_back(i);
    }
    b[n-k] = a[q.back()];

    return b;
}


int main(){
    int k = 3;//window size;
    int a[] = {1,4,5,6,2,5,4,2,10,23};
    int n = sizeof(a)/sizeof(a[0]);
    int *b = slidingWindow(a,n,k);
    for(int i = 0;i<n-k+1;i++){
        cout<<b[i]<<" ";
    }
    cout<<"\n";
    return 0;
}