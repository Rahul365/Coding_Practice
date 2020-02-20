#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll pow(ll x,ll y){
    if(y<=1) return 1;
    ll result = pow(x,y>>1);
    result *= (x * x);
    if(y&1)
     result *= x;
    return result;
}

ll powitr(ll x,ll y){
    ll result = 1;
    while(y!=0){
        if(y&1){
            result *= x;
        }
        y >>= 1;
        x*= x;
    }
    return result;
}

int main(){
    ll x = 66;
    ll y = 5;

    cout<<pow(x,y)<<" "<<powitr(x,y)<<"\n";
    return 0;
}