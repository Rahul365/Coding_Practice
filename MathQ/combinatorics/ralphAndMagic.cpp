#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
using ull = unsigned long long int;
template<typename T>
void read(T &x){
    if(typeid(x) == typeid(int)){
        scanf("%d",&x);
    }
    else if(typeid(x) == typeid(long long int)){
        scanf("%lld",&x);
    }
    else if(typeid(x) == typeid(double)){
        scanf("%f",&x);
    }
}
template<typename T>
void print(T x){
    if(typeid(x) == typeid(int)){
        printf("%d\n",x);
    }
    else if(typeid(x) == typeid(long long int)){
        printf("%lld\n",x);
    }
    else if(typeid(x) == typeid(unsigned long long int)){
        printf("%u\n",x);
    }
    else if(typeid(x) == typeid(double)){
        printf("%f\n",x);
    }
}


const ll mod = 1e9+7;
ll power(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1LL;
    }
    return r;
}
// https://codeforces.com/contest/894/problem/B
int main(){
    /*
        1st point  here : 
        if n  & m have different parity and k == -1 , then it is impossible to find any solution
        e.g. n = 1 , m = 4 and k = -1 -> no solution
    */
    long long int n,m,k;
    read(n);
    read(m);
    read(k);
    // cerr << (n&1) <<" " << (m&1) << " = " <<k <<"\n";
    if((n&1LL) != (m&1LL) && k == -1){
        print(0);
    }
    else{
        ll ans = power(2LL,n-1LL);
        ans = power(ans,m-1LL)%mod;
        print(ans);
    }
    return 0;
}