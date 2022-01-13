#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        int coins[n];
        // int ans = 0;
        for(int i = 0;i<n;++i){
            char ch;
            cin >> ch;
            coins[i] = (ch == 'H' ? 1: 0);
            // if(i < n-k)
            // ans += coins[i];
        }
        bool flip = false;
        for(int i = n-1;i>=n-k;--i){
            if(flip){
                coins[i] = 1-coins[i];
            }
            if(coins[i] == 1){
                flip = !flip;
            }
        }

        int ans = 0;
        for(int i= 0;i<n-k;++i){
            if(flip){
                ans += (1-coins[i]);
            }
            else
            {
                ans += coins[i];
            }
            
        }
        cout << ans <<"\n";
    }
    return 0;
}