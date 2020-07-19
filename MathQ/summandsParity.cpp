#include<bits/stdc++.h>
using namespace std;


int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        //represent n as sum of k even parity numbers or k odd parity numbers
        if(n&1 && k&1^1){//sum is odd and k even ,such sum is not possible 
            cout << "NO\n";
            continue;
        }
        
        if(n&1^1 && k&1){//sum is even and k is odd
            if(n < 2*k){
                cout <<"NO\n";
                continue;
            }
            for(int i= 0;i < k-1;++i) cout << "2 ";
            cout << n-2*(k-1) <<"\n";
        }
        else{
            if(n < k){
                cout <<"NO\n";
                continue;
            }
            for(int i= 0;i<k-1;++i) cout <<"1 ";
            cout << n -k+1 <<"\n";
        }
    }
    return 0;
}