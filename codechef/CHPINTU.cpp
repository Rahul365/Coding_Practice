#include<bits/stdc++.h>
using namespace std;
const int maxm = 100;
int sum[maxm];

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n>> m;
        int ids[n];
        memset(sum,-1,sizeof sum);
        for(int i = 0;i<n;++i){
            cin >> ids[i];
            sum[ids[i]] = 0;
        }
        int ans = INT_MAX;
        
        for(int i=0;i<n;++i){
            int price;
            cin >> price;
            sum[ids[i]]+=price;
        }
        for(int i = 0;i<=m;++i)
        {
            if(sum[i] == -1) continue;
            ans = min(ans,sum[i]);
        }
        cout << ans << "\n";
    }
    return 0;
}