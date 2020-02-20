#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+11;

vector<int> pom;
set<int> com;//components of zero edges
vector<int> Sizes(MAXN,0);
vector<int> par(MAXN,-1);
vector<int> odw(MAXN,0);
vector<int> g[MAXN];

int getroot(int x){
    while(x!=par[x]){
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void wunionii(int x,int y){
    // cout<<"wunionii..."<<"\n";
    int rx = getroot(x);
    int ry = getroot(y);
    if(rx == ry) return;
    if(Sizes[rx] < Sizes[ry]){
        swap(rx,ry);
    }
    par[ry] = rx;
    Sizes[rx] += Sizes[ry];
    com.erase(ry);
}

void solve(){
    int n,m;
    cin>>n>>m;
    int x,y;

    
    for(int i = 0;i<m;i++){
        cin>>x>>y;
        if(x < y) swap(x,y);
        g[x].push_back(y);
    }


    for(int i = 1;i<=n;i++){
        Sizes[i] = 1;    
        par[i] = i;
        for(int j : g[i]){
            int r = getroot(j);
            odw[r]++;//number of edges of weight 1 in the component r
        }

        for(int u : com){
            int r = getroot(u);
            // cout<<i<<":"<<r<<"\n";
            // cout<<odw[r]<<" "<<Sizes[r]<<"\n";
            if(odw[r] < Sizes[r]){
                pom.push_back(r);
            }
        }

        com.insert(i);
        for(int x : pom){
            wunionii(x,i);
        }
        pom.clear();
        for(int j : g[i]){
            odw[getroot(j)] = 0;
        }
    }

    cout<<(com.size()-1)<<"\n";

}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    solve();
    return 0;
}