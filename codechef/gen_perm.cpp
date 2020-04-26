#include<bits/stdc++.h>
using namespace std;

int main(){
    int n , k;
    cin >> n >> k;
    srand(time(NULL));
    cout << n << " " << k<<"\n";
    for(int i = 0;i<k;++i){
        set<int> s;
        for(int i= 1;i<=n;++i){
            s.insert(i);
        }
        int cnt = 0;
        while(cnt!=n){
            int x = rand()%(n+1);
            if(s.find(x)==s.end()) continue;
            s.erase(x);
            ++cnt;
            cout <<x <<" ";
        }
        cout <<"\n";
    }
    return 0;
}