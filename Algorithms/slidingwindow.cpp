#include<bits/stdc++.h>
using namespace std;


void printmaxinwindow(int *a,int n,int k){
    //process first window
    int N = n-k+1;
    int B[n-k+1];
    int id = 0;
    deque<int> q;
    for(int i =0;i<k;i++){
        while(!q.empty() && a[q.back()] <= a[i]){
            q.pop_back();
        }
        q.push_back(i);
    }

    for(int i = k;i<=n;i++){
        B[id++] = a[q.front()];
        if(i == n) break;
        //remove the elements not in the current window
        while(!q.empty() && q.front()<=i-k){
            q.pop_front();
        }

        while(!q.empty() && a[q.back()] <= a[i]){//pop those elements from the back that are less than or equal to current element
            q.pop_back();
        }
        q.push_back(i);
    }

    for(int i =0;i<N;i++){
        cout<<B[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    int a[] = {2,3,3,54,11,2,12,2,4,80};
    int n = sizeof(a)/sizeof(a[0]);
    int k = 3;
    printmaxinwindow(a,n,k);
    return 0;
}