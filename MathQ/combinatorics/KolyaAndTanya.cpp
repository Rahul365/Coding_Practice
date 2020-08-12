#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
// https://codeforces.com/problemset/problem/584/B
template<typename T>
T pmod(T a,T b,T m){
    T r = 1;
    while(b){
        if(b&1){
            r = (r * a)%m;
        }
        a = (a * a)%m;
        b >>= 1;
    }
    return r;
}

int main(){
    long long int n;
    cin >> n;
    //for n = 1, answer = 3^3 - 3! - 1
    //i.e (total number of ways to distribute coins among a triplet of gnome) - (number of triplets that sum upto 6) - (special triplet (2,2,2) that sum upto 6)
    //ans = (3^(3*n)) - (7^n)
    cout << ((pmod<long long int>(3LL,3LL*n,mod*1LL) - pmod<long long int>(7LL,n,mod*1LL))%mod + mod)%mod <<"\n";
    return 0;
}