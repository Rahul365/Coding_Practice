#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,k;
        scanf("%d%d",&n,&k);
        vector<int> a(n+1);
        for(int i = 1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        vector<ll> odd(n+1);
        vector<ll> even(n+1);
        //Observation 
        //For any subsequence of length >= 1
        //there are 3 possibilities : (even,odd),(odd,odd),(even,even)
        //Thus best way to maximize the sum is to pick (MAX ODD SUM + MAX EVEN SUM)
        //(two odd numbers can be added only iff  they are at distance > k from each other
        // i.e. if(a[i] & 1) odd[i] = max(odd[i-1],a[i] + (i-k-1 >= 0?odd[i-k-1]:0));
        //Similarly for even numbers even[i] = max(even[i-1],a[i] + (i-k-1 >= 0?even[i-k-1]:0));
        //Thus final answer is (odd[n] + even[n])
        for(int i = 1;i<=n;++i){
            odd[i] = odd[i-1];
            even[i] = even[i-1];
            if(a[i]&1){
                    odd[i] = max(odd[i],a[i] + (i-k-1>=0?odd[i-k-1]:0));
            } 
            else{
                    even[i]  =max(even[i],a[i] + (i-k-1>=0?even[i-k-1]:0));
            }
        }
        printf("%lld\n",odd[n] + even[n]);
    }
    return 0;    
}