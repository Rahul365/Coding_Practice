#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/617/B

int main(){
    int n;
    scanf("%d",&n);
    vector<int> a(n);
    for(int i =0;i<n;++i)
    {
        scanf("%d",&a[i]);
    }
    long long int ans = 1;
    int l = 0; while(l < n  && a[l] == 0) ++l;
    int r = n-1; while(r >= 0 && a[r] == 0) --r;
    if(l > r){
        cout << 0 <<"\n";
        return 0;
    }
    int p_l = l;
    for(int i = l+1;i<=r;++i){
        a[i] += a[i-1];
        if(a[i] > a[i-1])
        {
            // cerr << i << " " << p_l << " : " << (i-p_l) <<"\n";
            ans *= (i-p_l<=0?1:i-p_l);
            p_l = i;
        }
    }
    printf("%lld\n",ans);
    return 0;
}