#include<bits/stdc++.h>
using namespace std;

bool isprime(int n){
    if(n < 2) return false;
    if(n%2 == 0) return n==2;
    if(n%3 == 0) return n==3;
    if(n > 6 && ((n-1)%6!=0 && (n+1)%6!=0)) return false; 
    int cnt = 0;
    for(int i = 2;i*i<=n;++i){
        if(n%i == 0){
            return false;
            while(n%i == 0)
                n/=i;
        }
    }
    if(n > 1 && ++cnt > 1) return false;
    return cnt == 1;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        for(int i = n;i<=m;++i){
            if(isprime(i))
                cout << i << "\n";
        }
        cout<<"\n";
    }
    return 0;
}