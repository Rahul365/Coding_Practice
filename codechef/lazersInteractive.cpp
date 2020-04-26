#include<bits/stdc++.h>
using namespace std;
//Probability of failure is too low
//given the ranges of L and R in the substask constraints
int main(){
    int t;
    cin >> t;
    while(t--){
        int n , m , k, q;
        cin >> n >> m >> k >> q;
        pair<int,int> Q[q];
        for(int i = 0;i<q;++i)
            cin >>Q[i].first >> Q[i].second;
        if(n == 20000){
            cout <<2 <<" ";
            for(int i = 0;i<q;++i){
                cout << (m-1) <<" ";
            }
            cout<<"\n";
            fflush(stdout);
        }
        else{
            vector<int> ans(q);
            for(int i = 0;i<min(k,q);++i){
                cout << 1 << " " << Q[i].first << " "<< Q[i].second <<" " <<(m>>1)<<"\n"; fflush(stdout);
                cin >> ans[i];
            }
            cout << 2 <<" ";
            for(int i = 0;i<q;++i)
                cout << ans[i] << " ";
            cout <<"\n";
            fflush(stdout);
        }
        int ok;
        cin >> ok;
        if(ok == -1)
            exit(0);
    }
    return 0;
}