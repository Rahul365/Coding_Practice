#include<bits/stdc++.h>
using namespace std;
/***
 * To compute P.(Q^-1) modulo (1000000007)
*/
const int maxn = 1e5 +11;
using ll = long long int;
const ll mod = 1e9 +  7;

template<typename T>
T power(T a,T b){
    T r = 1;
    while(b){
        if(b&1){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1;
    }
    return r;
}

ll nodes[maxn];
ll valid[maxn];

void countNodes(){
    nodes[0] = 1;
    valid[0] = 0;
    for(int i = 1;i<maxn;++i){
        nodes[i] = 2LL*nodes[i-1];
        nodes[i] %= mod;
        //valid pair at depth i = (number of nodes at depth i * (ancestors at odd distances)) + valid pairs at depth i-1
        valid[i] = (nodes[i]*((i+1)>>1LL)) + valid[i-1];
        valid[i] %= mod;
    }
}
//to compute PQ^-1 % mod
template<typename T>
T compute(T P,T Q){
    Q = power(Q,mod-2);
    return (P*Q)%mod;
}

int main(){
   countNodes();
    int t;
    scanf("%d",&t);
    while(t--){
        int d;
        scanf("%d",&d);
        ll total = nodes[d+1]-1;
        total *= (total-1);
        total %= mod;

        ll ans = valid[d];
      //  cerr << ans << " " <<total << "\n";
      //compute (p.(q^-1))%mod as answer
      /* 
      //AC solution
        ans  *= power(total,mod-2);
        ans  %= mod;
        printf("%lld\n",ans);
    */
        printf("%lld\n",compute(ans,total));
    }
    return 0;
}