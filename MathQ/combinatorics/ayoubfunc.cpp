#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
long long int count(int n){
    return (1LL*n*(n+1))/2;
}

// https://codeforces.com/problemset/problem/1301/C
/* Note : Still didn't get the solution after reading editorial*/
int main(){
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        ll answer = 0;
        if(m>0){
            if(n == m){
                answer = count(n) - 1; 
            }
            else if(m >= n/2){
                answer = m + count(n-1);
            }
            else{
                
            }
        }
        cout << answer <<"\n";
    }
    return 0;
}