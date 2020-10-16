#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+11;
vector<int> g[maxn];
vector<int> p(maxn);

void dfs(int u,int par){
    p[u] = par;
    for(int v : g[u]){
        if(v == par) continue;
        dfs(v,u);
    }
}

int main(){
    int n,m;
    cin >> n >>m;
    for(int i = 0;i<n-1;++i){
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1,1);
    
    return 0;
}