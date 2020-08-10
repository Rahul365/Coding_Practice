#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/251/A
int main(){
    int n,d;
    scanf("%d%d",&n,&d);
    vector<int> a(n);
    for(int i =0;i<n;++i){
        scanf("%d",&a[i]);
    }
    long long int ans = 0;
    auto count = [&](long long int v){
        return (v*(v-1))>>1;
    };
//strictly increasing
    for(int i = 0;i<n;++i){
        int l = i+1;
        int r = n-1;
        int pos = -1;
        while(l <= r){
            int m = l+(r-l)/2;
            if(a[m] <= a[i] + d){
                pos = m;
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        if(pos == -1){
            continue;
        }
        int rem = pos - i;
        ans+=count(1LL*rem);
    }
    printf("%lld\n",ans);
    return 0;
}