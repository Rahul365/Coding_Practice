#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int a,b,q;
        scanf("%d%d%d",&a,&b,&q);
        int n = a*b;
        vector<ll> pref(n+1,0);
        for(int i= 1;i<=n;++i){
            pref[i] = pref[i-1];
            if((i%a)%b != (i%b)%a){
                ++pref[i];
            }
        }
        
        /**
             *  count all such x such that (x%a)%b!=(x%b)%a and l <= x <= r
             *  constraints :
             *  1 <= l,r <= 10^18
             *  1 <= a,b <= 200
             *  So we know that (x%(a*b)) => ((x%a)%b)
             *  ((ab + x)%a)%b => ((x%a)%b) => x%(a*b)
             * it will hold for range [0,....,(a*b)-1]
        */
       /*Number of elements 'x' such that  0<=x<=l, such that  (x%a)%b!=(x%b)%a*/
        auto read = [&](ll l){
            ll cnt = l/n;//number of proper segments of length [a*b]
            ll rem = l%n;//length of remaining segment
            return pref[n]*cnt + pref[rem];
        };

        while(q--){
            ll l,r;
            scanf("%lld%lld",&l,&r);
            //[0,r] - [0,l-1]
            printf("%lld ",read(r)-read(l-1));
        }
        printf("\n");
    }
    return 0;
}