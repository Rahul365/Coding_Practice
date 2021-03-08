#include<bits/stdc++.h>
using namespace std;
using ll = int64_t;
const ll mod = 998244353;
int getlen(int n){
    int cnt = 0;
    while(n){
        ++cnt;
        n/=10;
    }
    return cnt;
}

ll power(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1)
         r = (r * a)%mod;
        a = (a * a)%mod;
        b>>=1;
    }
    return r;
}

void addself(ll &a,ll b){
    a += b;
    if(a >= mod) a-=mod;
    else if(a < 0) a+=mod;
}

// https://codeforces.com/problemset/problem/1195/D2
int main(){
    int n;
    cin >> n;
    vector<int> ele_len(11,0);
    vector<pair<int,int>> arr(n);
    
    for(int i =0 ;i<n;++i){
        cin >> arr[i].first;
        arr[i].second = getlen(arr[i].first);
        ele_len[arr[i].second]++;
    }

    auto count = [](ll p,ll val_p,ll q,ll val_q){
        //cerr <<"p : "<<p <<" , q : "<< q<<"\n";
        ll res = 0;
        if(val_p){
            ll pw = 10;
            if(p >= q){
                for(int i = p;i>=p-q+1;--i){
                    addself(res,(pw*(val_p%10))%mod);
                    val_p/=10;
                    pw=(pw*100)%mod;
                }
                if(val_p) pw = (pw * power(10LL,mod-2LL))%mod;
                while(val_p){
                    addself(res,(pw*(val_p%10))%mod);
                    val_p/=10;
                    pw = (pw*10)%mod;
                }
            }
            else{
               for(int i = 1;i<=p;++i){
                    addself(res,(pw*(val_p%10))%mod);
                    val_p/=10;
                     pw=(pw*100)%mod;
               }
            }
        }
        else if(val_q){
            ll pw = 1;
            if(p >= q){
                for(int i = 1;i<=q;++i){
                    addself(res,(pw*(val_q%10))%mod);
                    val_q /= 10;
                    pw = (pw*100)%mod;
                }
            }
            else{
                //p < q
                for(int i = q-p;i<=q;++i){
                    addself(res,(pw*(val_q%10))%mod);
                    val_q /= 10;
                    pw = (pw*100)%mod;
                }
                if(val_q) pw = (pw * power(10LL,mod-2LL))%mod;
              
                while(val_q){
                    addself(res,(pw*(val_q%10))%mod);
                    val_q /= 10;
                    pw =(pw*10)%mod;
                }
            }
        }
        return res;
    };

    ll answer = 0;
    for(int i = 0;i<n;++i){
        ll curr = arr[i].first;
        ll len = arr[i].second;
        //cerr <<"curr : "<<curr<<"\n";
        for(int j = 1;j <= 10;++j){
            ll freq = ele_len[j];
            if(!freq) continue; 
            ll res = count(len,curr,j,0LL);
            //cerr << res*freq<<"\n";
            addself(answer,(freq*res)%mod);
            //if(len == j) continue;
            res = count(j,0LL,len,curr);
            //cerr << res*freq<<"\n";
            addself(answer,(freq*res)%mod);
        }
    }
    cout << answer <<'\n';
    return 0;
}