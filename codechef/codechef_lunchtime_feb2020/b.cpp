#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+4;
int a[maxn];
int f[maxn];

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        memset(f,0,sizeof f);
        for(int i = 1;i<=n;++i){
            cin >> a[i];
        }
        int ans = 0;
        int i = 1;
        int j = 1;
        int cnt = 0;
        while(j <= n){
            if(++f[a[j]] == 1){
                ++cnt;
            }
            if(cnt <= k-1){
                ans = max(ans ,j-i+1);
            }
            else if(cnt == k){
                while(i <= j && cnt == k){
                    if(--f[a[i]] == 0){
                        --cnt;
                    }
                    ++i;
                }
            }
            ++j;
        }
        cout << ans <<"\n";
    }
    return 0;
}