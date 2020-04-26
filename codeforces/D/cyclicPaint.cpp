// https://codeforces.com/contest/1328/problem/D
#include<bits/stdc++.h>
using namespace std;


int main(){
    int q;
    cin >> q;
    while(q--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0;i < n;++i){
            cin >> a[i];
        }
        bool same = true;
        bool triplet = false;
        for(int i =1;i<n;++i){
            if(a[i-1]!=a[i]) {
                same =false;
                break;
            }
            
        }

        if(same){
            cout << 1<< "\n";
            for(int i = 0;i<n;++i){
                cout << 1 << " ";
            }
            cout<<"\n";
            continue;
        }
        else if(n%2 == 0){
            cout << 2 <<"\n";
           for(int i= 0;i<n;++i){
               cout << (i%2 + 1) <<" ";
           }
            cout<<"\n";
            continue;
        }
        bool up = false;
        for(int i = 0;i<n;++i){
            if(a[i] == a[(i+1)%n])
            {
                vector<int> ans(n);
                int v = 0;
                for(int pos = i+1;pos < n;++pos){
                    ans[pos]  = v +1;
                    v ^= 1; 
                }
                v = 0;
                for(int pos= i;pos >= 0;--pos){
                    ans[pos] = v +1;
                    v ^= 1; 
                }
                cout << 2 <<"\n";
                for(int i =  0 ;i <n;++i){
                   cout << ans[i] << " ";
                }
                cout <<"\n";
            up = true;
            break;
            }
        }
        if(up) continue;
        cout << 3 <<"\n";
        for(int i = 0;i<n-1;++i){
            cout << (i%2 + 1) << " ";
        }
        cout <<3<< "\n";
    }
    return 0;
}