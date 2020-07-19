#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
ll best;
bool equal(ll *a,ll *b){
    for(int i = 0;i<3;++i) if(a[i]!=b[i]) return false;
    return true;
}

ll mulf(ll a,ll b){
    if(a && b%a == 0) return b/a;
    return 0LL;
}

//b1 = a1*x + c
//b2 = a2*x + c
//b1-b2 = x*(a1-a2)
void solve(ll *a,ll *b,ll moves = 0){
    if(moves >= best) return;
    if(equal(a,b)){
        best = min(best , moves);
        cerr <<"Yes "<<best<<"\n";
        return;
    }
    if(moves >= 2) return;
    set<ll> add;
    set<ll> mul;
    for(int i = 0;i<3;++i)
        add.insert(b[i]-a[i]);
    mul.insert(0);
    for(int i = 0;i<3;++i)
        if(a[i] && b[i]%a[i] == 0)
        mul.insert(b[i]/a[i]);
    for(int i = 0;i<3;++i)
        mul.insert(mulf(a[i]-a[(i+1)%3],b[i]-b[(i+1)%3]));
    for(int i = 1;i<=7; ++i){
        vector<ll> cd;
        for(int j=0;j<3;++j) if(i&(1<<j)) cd.push_back(j);
        for(auto plus : add){
            ll aa[3];
            for(int j = 0;j<3;++j) aa[j] = a[j];
            for(auto id:cd) aa[id]+=plus;
            solve(aa,b,moves+1);
        }
        for(auto mult : mul){
            ll aa[3];
            for(int j = 0;j<3;++j) aa[j] = a[j];
            for(auto id : cd) aa[id]*=mult;
            solve(aa,b,moves+1);
        }
    }
}

void testcase(){
    ll a[3];//source values
    ll b[3];//target values
    best = 3;
    for(int i =0 ;i<3;++i){
        cin >> a[i];
    }
    for(int i =0 ;i<3;++i){
        cin >> b[i];
    }
    solve(a,b,0);
    cout << best <<"\n";
}
int main(){
    int t;
    cin>> t;
    while(t--){
        testcase();
    }
}