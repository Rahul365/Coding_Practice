#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9+7;
const int LG = 20;
const int maxn = 1e5+1;
int a[maxn];
int LOG[maxn+1];
int sp[maxn][LG];
/*
    Build Sparse Min Matrix
*/
void computelog(){
    LOG[1] = 0;
    for(int i = 2;i<=maxn;++i){
        LOG[i] = LOG[i>>1] + 1;
    }
}

void init(){
     for(int  i = 0;i<maxn;++i)
        for(int j = 0;j<LG;++j)
            sp[i][j] = inf;
}

/*O(1) per query*/
void RMinQ(int n){
    init();
    for(int i = 0 ;i< n;++i)
        sp[i][0] = a[i];//min of all elements from [i,i+(2^0))
    

    for(int l = 1;l<LG;++l){
        for(int i = 0;i+(1<<l)<=n;++i){
            if(sp[i][l-1]!=inf){
                sp[i][l] = min(sp[i][l-1],sp[i+(1<<(l-1))][l-1]);    
            }
        }
    }
    //sp[i][j] = min(a[i] ... a[i+(1<<j)-1])
    //sp[i][j] = min(sp[i][j-1],sp[i+(1<<(j-1))][j-1])
    //sp[i][j-1] = min(a[i],....,a[i+(1<<(j-1))-1]
    //sp[i+(1<<(j-1))][j-1] = min(a[i+(1<<(j-1))],a[i+(1<<j)-1]);

    for(int l = 0;l < LG;++l){
        for(int i = 0;i<n;++i){
            cout << sp[i][l] << " \n"[i==n-1];
        }
    }
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        if(l > r) swap(l,r);
        int d = LOG[r-l+1];
        int ans = min(sp[l][d],sp[r- (1<<d) + 1][d]);
        cout << ans <<"\n";
    }
}
/*O(log(maxn)) per query*/
void RSQ(int n){
    init();
    for(int i = 0 ;i<n;++i)
        sp[i][0] = a[i];

    for(int L = 1;L<LG;++L){
        for(int i = 0;i+(1<<L)<=n;++i){
            sp[i][L] = sp[i][L-1] + sp[i+(1<<(L-1))][L-1];
        }
    }
    
    int q;
    cin >> q;
    while(q--){
        int l ,r; 
        cin >> l >> r;
        int sum = 0;
        for(int L = LG-1;L>=0;--L)
            if((1<<L) <= r-l+1){
                sum += sp[l][L];
                l+=(1<<L);
            }
        cout << sum <<"\n";
    }
}

int main(){
    
    computelog();
    memset(a,inf,sizeof a);
    

    int n;
    cin >> n;
    for(int  i = 0;i<n;++i){
        cin >> a[i];
    }
    
    RMinQ(n);
    // RSQ(n);
    return 0;
}