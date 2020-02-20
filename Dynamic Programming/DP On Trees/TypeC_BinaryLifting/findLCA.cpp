#include<bits/stdc++.h>
using namespace std;
const int N = 2e5;
const int LG = 20;

vector<int> g[N];
int level[N],P[N][LG];
//P[N][LG] -> tells the ancestor of a node N at distance 2^LG from it upwards
//1 based Indexing
void dfs(int u,int par){
    level[u] = 1 + level[par];
    P[u][0] = par;//parent of node at distance 2^0 == 1 
    for(int v : g[u]){
        if(v == par) continue;
        dfs(v,u);
    }
}


int lca(int u,int v){
    int i,lg;

    if(level[u] < level[v]) swap(u,v);//generalization so that node to be lifted is always u
    //find distance lg which is closest to level of node u
    //i.e. when 1<<lg > level[u] then 1<<(lg-1) is the closest distance to node at level[u]
    for(lg = 0 ; (1<<lg)<=level[u]; ++lg);

    --lg;//level of node u
    //lift node u to the same level as node v
    for(i = lg;i>=0;i--){  
        if(level[u] - (1<<i) >= level[v]){
            u = P[u][i];
        }
    }

    if(u == v){//if v itself is the ancestor of node u at distance 2^i from it
        return u;
    }

    for(i = lg;i>=0;i--){
        if(P[u][i]!=-1 && P[u][i]!=P[v][i]){
            u = P[u][i],v = P[v][i];
        }
    }
    return P[u][0];
}

/**
 * To find the distance between two nodes in a tree
*/
int distance(int x,int y){
    return level[x] + level[y] - 2*level[lca(x,y)];
}

/**
 * Find the ancestor for given node u at distance d from above
*/
int findAncestor(int u,int d){
    d = level[u] - d;//ancestor for node u will be at distanceUpFromNode = level[node] - distanceFromAbove 

    int i,lg;
    for(lg = 0;(1<<lg)<=level[u];++lg);
    lg--;

    for(i = lg;i>=0;i--){
        if(level[u] - (1<<i) >= d){
            u = P[u][i];
        }
    }
    return u;
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n;//number of nodes
    cin>>n;
    int u,v;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 0;i<LG;i++){
        for(int j = 0;j<n+1;j++)
            P[j][i] = -1;
    }

    level[0] = -1;
    dfs(1,0);//compute the level of each node and set parent of each node at distance 2^0 i.e P[node][0]

    for(int i = 1;i<LG;i++){
        for(int j = 1;j<=n;j++){
            if(P[j][i-1] != -1){
                P[j][i] = P[P[j][i-1]][i-1];
            }
        }
    }

    int x,y;
    cin>>x>>y;
    cout<<lca(x,y)<<"\n";
    cout<<findAncestor(y,2)<<"\n";
    return 0;
}