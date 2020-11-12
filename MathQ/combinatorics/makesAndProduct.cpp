#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
template<typename T>
T count(T  n){
    return (n*(n-1))/2;
}

// https://codeforces.com/problemset/problem/817/B
int main(){
    int n;
    cin >> n;
    map<int,int> cnt;
    for(int i = 0;i<n;++i){
        int v;
        cin >> v;
        ++cnt[v];
    }
    auto it = cnt.begin();
    array<int,3> arr;
    for(int i = 0;i<3;++i){
        arr[i] = it->second;
        ++it;
    }
    
    ll answer = 0;
    if(arr[0] >= 3){
        for(ll i = arr[0];i-3>=0;--i){
            answer += count(i-1);
        }
    }
    else if(arr[0]+arr[1]>=3){
        if(arr[0] == 1){
            answer += count((ll)arr[1]);/*number of pairs from the second number*/
        }
        else
        {   assert(arr[0] == 2);
            answer = arr[1];
        }
    }
    else{
        assert(arr[2]>=1);
        answer = arr[2];
    }
    cout << answer <<"\n";
    return 0;
}