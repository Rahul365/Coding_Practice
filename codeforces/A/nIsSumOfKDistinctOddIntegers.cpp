#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    int t;
    cin >> t;
    while(t--){
        ll n,k;
        cin >> n >> k;
        if(k*k <= n && (((n&1) && (k&1)) or (!(n&1) && !(k&1))))
            cout <<"YES\n";
        else 
            cout <<"NO\n";
    }
    return 0;
}