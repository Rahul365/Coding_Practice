#include<bits/stdc++.h>
#define printv(vec) for(auto v : vec) cerr << v <<' '; cerr<<'\n';
using namespace std;

vector <int> printMaxOfMin(int arr[], int N) {
    vector<int> nsm,psm;
    stack<int> stk;
    stk.push(0);
    psm.emplace_back(-1);
    for(int i = 1;i<N;++i){
        while(!stk.empty() && arr[stk.top()] >= arr[i]){
            stk.pop();
        }
        psm.emplace_back(stk.empty()?-1:stk.top());
        stk.push(i);
    }
    while(!stk.empty()){
        stk.pop();
    }
    printv(psm);
    stk.push(N-1);
    nsm.emplace_back(N);
    for(int i = N-2;i>=0;--i){
        while(!stk.empty() && arr[stk.top()] >= arr[i]){
            stk.pop();
        }
        nsm.emplace_back(stk.empty()?N:stk.top());
        stk.push(i);
    }
    reverse(nsm.begin(),nsm.end());
    printv(nsm);
    vector<int> ans(N);
    for(int i = 0;i<N;++i){
        int window_size = nsm[i] - psm[i]-1;
        cerr << window_size << " \n"[i==N-1];
        ans[window_size-1] = max(ans[window_size-1],arr[i]);
    }
    for(int i = N-2;i>=0;--i){
        ans[i] = max(ans[i],ans[i+1]);
    }
    return ans;
}

int main(){
    int arr[] = {10, 20, 30, 50, 10, 70, 30};
    int N = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0;i<N;++i){
        cout << arr[i]<< " \n"[i==N-1];
    }
    vector<int> ans = printMaxOfMin(arr,N);
    for(int v : ans)
    cout << v << " ";
    cout <<"\n";
    return 0;
}