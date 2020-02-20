#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        ll l,r;
        cin>>l>>r;
        ll ans = (l == 0 || r == 0)?1:0;
        vector<bool> dp(32,false);//represents the binary mask of a number
        map<ll,vector<bool>> num_to_bit;
        for(ll i = l ;i<=r;i++){
            // fill(dp.begin(),dp.end(),false);
            // for(int bit = 31;bit>=0;bit--){
            //     dp[bit] = (i&(1LL<<bit));
            // }
            // num_to_bit[i] = dp; 
            ll j = l;
            if(i+j == i^j) ans++;
            if(i&1 && !(j&1))
             j+=1;   
            else if(!(i&1) && !(j&1))
             j+=1;
            while(j <= r){
                if(i+j == i^j) ans++;
                j+=2;
            }
        }


        cout<<ans<<"\n";
    }
    
    return 0;
}