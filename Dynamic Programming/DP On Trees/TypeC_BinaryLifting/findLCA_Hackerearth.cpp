#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+11;
const int LG = 20;
int level[N],P[N][LG];
vector<int> g[N];
/**
 * link : https://www.hackerearth.com/problem/algorithm/lowest-common-ancestor/
 * 
*/

void dfs(int u,int par)
{
    P[u][0] = par;
    level[u] = 1 + level[par];
    for(int v : g[u]){
        if(v == par) continue;
        dfs(v,u);
    }
}

int lca(int u,int v){
    if(level[u] < level[v]) swap(u,v);
    
    int i,lg;
    for(lg = 0;(1<<lg) <= level[u];++lg);
    --lg;
    
    for(i = lg;i>=0;i--){
        if(level[u] - (1<<i) >= level[v]){
            u = P[u][i];
        }
    }
    
    if(u == v)
        return u;
    
    for(i = lg;i>=0;i--){
        if(P[u][i]!=-1 && P[u][i]!= P[v][i]){
            u = P[u][i];
            v = P[v][i];
        }
    }
    return P[u][0];
}

int main(){
    int n;
    cin>>n;
    int par;
    for(int i = 2;i<=n;i++){
        cin>>par;
        ++par;
        g[i].push_back(par);
        g[par].push_back(i);
    }
    
    int m;
    cin>>m;
    int query[m];
    for(int i= 0;i<m;i++){
        cin>>query[i];
        query[i]++;
    }
        
        
    for(int i = 0;i<LG;i++){
        for(int j = 0;j<=n;j++){
            P[j][i] = -1;
        }
    }
    
    level[0] = -1;
    
    dfs(1,0);
    
    for(int i = 1;i<LG;i++){
        for(int j = 1;j<=n;j++){
            if(P[j][i-1]!=-1){
                P[j][i] = P[P[j][i-1]][i-1];
            }
        }
    }
    
    int result = query[0];
    for(int i = 1;i<m;i++){
        result = lca(result,query[i]);
    }
    cout<<(result - 1)<<"\n";
    return 0;
}