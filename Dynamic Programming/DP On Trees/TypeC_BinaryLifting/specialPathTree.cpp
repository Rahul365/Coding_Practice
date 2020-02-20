/**
 * Link : https://www.hackerearth.com/fr/problem/algorithm/tough-tree/
 * 
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+11, LG = 20;
int level[N];
int P[N][LG];
int dist[N];
vector<pair<int,int>> g[N];


int lca(int u,int v){
    if(level[u] < level[v]) swap(u,v);
    int i,lg;
    for(lg = 0;(1<<lg) <= level[u];++lg);

    --lg;
    for(i = lg;i>=0;i--){
        if(level[u] - (1<<i) >= level[v])
        {
            u = P[u][i];
        }
    }

    if(u == v) return u;

    for(i = lg ; i>=0 ;i--){
        if(P[u][i]!=-1 && P[u][i]!=P[v][i]){
            u = P[u][i], v = P[v][i];
        }
    }
    return P[u][0];
}

void dfs(int u,int par){
    level[u] = 1 + level[par];
    P[u][0] = par;
    for(pair<int,int> p : g[u]){
        int v = p.first;
        if(v == par) continue;
        dist[v] = dist[u] + p.second;
        dfs(v,u);
    }
}

int main(){
    freopen("inputspecialpath.txt","r",stdin);
    freopen("outputspecialpath.txt","w",stdout);
    int n;
    cin>>n;
    int x,y,z;
    for(int i = 0;i<n-1;i++)
    {
        cin>>x>>y>>z;
        g[x].push_back({y,z});
        g[y].push_back({x,z});
    }

    for(int i = 0;i<LG;++i)
        for(int j = 0;j<n+1;j++)
            P[j][i] = -1;

    level[1] = -1;
    dist[1] = 0;
    dfs(1,1);

    for(int i = 1;i<LG;i++) 
        for(int j = 1;j<n+1;j++)
            if(P[j][i-1]!=-1){
                P[j][i] = P[P[j][i-1]][i-1];
            }
        
    int q;
    cin>>q;
    while(q--){
        cin>>x>>y>>z;
        int dx = dist[x] + dist[z] - 2*dist[lca(x,z)];
        int dy = dist[y] + dist[z] - 2*dist[lca(y,z)];
        cout<<dx-dy<<"\n";
    }

    return 0;
}