#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 11;
int deg[MAXN];

void solve(){
        int n,m;
        cin>>n>>m;
        memset(deg,0,sizeof(deg));

        int u,v;
        for(int i =  0;i<m;i++){
            cin>>u>>v;
            deg[u] ^= 1;
            deg[v] ^= 1;
        }

        if(!(m&1)){
            //even number of edges
            cout<<1<<"\n";//number of sets
            for(int i = 1;i<=n;i++)
                cout<<1<<" ";
            cout<<"\n";
            return;
        }

        for(int i = 1;i<=n;i++){
            if(deg[i]&1)
            {
                cout<<2<<"\n";//2 divisions
                for(int j = 1;j<=n;j++){
                    if(j!=i)
                        cout<<1<<" ";
                    else
                        cout<<2<<" ";
                }
                cout<<"\n";
                return;
            }
        }

        cout<<3<<"\n";//3 divisions
        //remove u and v
        for(int i = 1;i<=n;++i)
        {
            if(i == u) cout<<1<<" ";
            if(i == v) cout<<2<<" ";
            else cout<<3<<" ";
        }
        return;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}