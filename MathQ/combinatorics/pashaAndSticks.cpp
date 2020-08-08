#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/610/A
int main(){
    ll n;
    cin >> n;
    /*
        Divide n into 4 sides of rectangle Not square
        Count the number of rectangles possible
    */    
    if(n&1){
        cout << 0 <<"\n";
    }
    else{
        //n must be even so that it is possible to equally divided into 4 parts (l,l,b,b)
        ll cut = n>>1;
        //y < n/2
        //x = (n/2) - y
        ll l = 1;
        ll r = cut;
        ll ans = 0;
        while(l<=r){
            ll  m = (l+r)>>1;
            if(m < (cut - m)){
                ans = m;
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        cout << ans <<"\n";
    }
    return 0;
}