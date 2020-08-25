#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/131/C
long long int ncr(long long int n,long long int r){
    r = min(r,n-r);
    long long int p = 1,k = 1;
    while(r){
        p *= n;
        k *= r;
        long long int div = __gcd(p,k);
        p/=div;
        k/=div;
        --r;
        --n;
    }
    return p;
}

int main(){
    long long int n,m,t;
    cin >> n >> m >> t;
    /*composition of t members such that there is atleast 4 boys and 1 girl*/
    assert(t>=5);
    long long int answer = 0;
    for(long long int boys = 4;boys<=n;++boys){
        if(boys<=n && boys>=4 && t-boys>=1 && t-boys<=m)
        answer += ncr(n,boys)*ncr(m,t-boys); 
    }
    cout << answer <<"\n";
    return 0;
}