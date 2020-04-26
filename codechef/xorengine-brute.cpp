#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("xorengineinput.txt","r",stdin);
    freopen("xorenginebruteout1.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        int n,q;
        
        scanf("%d %d",&n,&q);
        int a[n];
        for(int i = 0;i<n;++i) scanf("%d",&a[i]);
        
        while(q--){
            int x;
            scanf("%d",&x);
            int even = 0;
            for(int i= 0;i<n;++i){
                int b = a[i] ^ x;
                if(!(__builtin_popcount(b) & 1)) ++even;
            }
            printf("%d %d\n",even,n-even);
        }
    }
    return 0;
}