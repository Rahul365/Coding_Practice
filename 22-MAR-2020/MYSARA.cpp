#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 1e9 + 7;
//https://www.codechef.com/COOK116A/problems/MYSARA
template<typename T>
T power(T x,T n){
    T r = 1;
    while(n){
        if(n&1)
        r = (r * x)%mod;
        x = (x * x)%mod;
        n >>= 1;
    }
    return r;
}


int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0;i<n;++i)
        {
            cin >> a[i];
        }
        
        int ans = 1;
        for(int i = 1;i<n;++i){
            if((a[i] & a[i-1])!=a[i-1])//check if a[i-1] is a subset of a[i] or not
            {
                //no such sequence is possible
                ans = 0; break;
            }
            ans = (1LL * ans * power(2,__builtin_popcount(a[i-1])))%mod;
        }
        cout << ans <<"\n";
    }
    return 0;
}